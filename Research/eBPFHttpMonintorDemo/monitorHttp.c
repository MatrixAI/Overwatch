// Source: https://github.com/iovisor/bcc/blob/master/examples/networking/http_filter/

#include <uapi/linux/ptrace.h>
#include <net/sock.h>
#include <bcc/proto.h>

#define IP_TCP 	6
#define ETH_HLEN 14
#define NUM_EXC 10

// key type and leaf type for BPF Hashmap
struct Key {
	u32 src_ip;               //source ip
	u32 dst_ip;               //destination ip
	unsigned short src_port;  //source port
	unsigned short dst_port;  //destination port
};

// hashmap for request/response matching, with timestamp as value
BPF_HASH(sessions, struct Key, u64, 10);

// array of processing times / latency values
// TODO: need to udpate this to separate values by session/host
BPF_ARRAY(records, u64, NUM_EXC);

// counting number of http request[0] and response[1] messages
// [3] for latency array index counting
BPF_ARRAY(counters, u64, 3);

// logs
BPF_HASH(logs, u64, struct Key, NUM_EXC * 4);

/*eBPF program.
	Locate HTTP/TCP/IP packets with non-empty payload
	Record incoming GET requests and corresponding HTTP responses
	Measures number of request/response exchanges and service delay
  if the program is loaded as PROG_TYPE_SOCKET_FILTER
  and attached to a socket
  return  0 -> DROP the packet
  return -1 -> KEEP the packet and return it to user space (userspace can read it from the socket_fd )
 */

int http_filter(struct __sk_buff *skb) {

	// grab timestamp
	u64 ts = bpf_ktime_get_ns();

	u8 *cursor = 0;

	struct ethernet_t *ethernet = cursor_advance(cursor, sizeof(*ethernet));
	// drop if not ip packet
	if (!(ethernet->type == 0x0800)) {
		goto DROP;
	}

	struct ip_t *ip = cursor_advance(cursor, sizeof(*ip));
	// drop if not TCP packets (ip next protocol = 0x06)
	if (ip->nextp != IP_TCP) {
		goto DROP;
	}

	u32  tcp_header_length = 0;
	u32  ip_header_length = 0;
	u32  payload_offset = 0;
	u32  payload_length = 0;
	struct Key key;

	//calculate ip header length
	//value to multiply * 4
	//e.g. ip->hlen = 5 ; IP Header Length = 5 x 4 byte = 20 byte
	ip_header_length = ip->hlen << 2;    //SHL 2 -> *4 multiply

  //check ip header length against minimum
	if (ip_header_length < sizeof(*ip)) {
		goto DROP;
	}

  //shift cursor forward for dynamic ip header size
  void *_ = cursor_advance(cursor, (ip_header_length-sizeof(*ip)));

	struct tcp_t *tcp = cursor_advance(cursor, sizeof(*tcp));

	//retrieve ip src/dest and port src/dest of current packet
	//and save it into struct Key
	key.dst_ip = ip->dst;
	key.src_ip = ip->src;
	key.dst_port = tcp->dst_port;
	key.src_port = tcp->src_port;

	//calculate tcp header length
	//value to multiply *4
	//e.g. tcp->offset = 5 ; TCP Header Length = 5 x 4 byte = 20 byte
	tcp_header_length = tcp->offset << 2; //SHL 2 -> *4 multiply

	//calculate payload offset and length
	payload_offset = ETH_HLEN + ip_header_length + tcp_header_length;
	payload_length = ip->tlen - ip_header_length - tcp_header_length;

	//http://stackoverflow.com/questions/25047905/http-request-minimum-size-in-bytes
	//minimum length of http request is always geater than 7 bytes
	//avoid invalid access memory
	//include empty payload
	if(payload_length < 7) {
		goto DROP;
	}

	//load first 7 byte of payload into p (payload_array)
	//direct access to skb not allowed
	unsigned long p[7];
	int i = 0;
	int j = 0;
	const int last_index = payload_offset + 7;
	for (i = payload_offset ; i < last_index ; i++) {
		p[j] = load_byte(skb , i);
		j++;
	}

	// only match GET requests and responses for now
	//HTTP
	if ((p[0] == 'H') && (p[1] == 'T') && (p[2] == 'T') && (p[3] == 'P')) {
		// response found
		counters.increment(1);
		logs.update(&ts, &key);

		int zero = 0;
		struct Key lookupKey = {
			.src_ip = key.dst_ip,
			.dst_ip = key.src_ip,
			.src_port = key.dst_port,
			.dst_port = key.src_port
		};

		u64 *req_ts = sessions.lookup(&lookupKey);
		if(req_ts){
			u64 elapsed = ts - *req_ts;
			int two = 2;
			u64 *pidx = counters.lookup(&two);
			if(pidx) {
				int idx = *pidx;
				records.update(&idx, &elapsed);
			}
			counters.increment(2);
			sessions.delete(&lookupKey);
		}
		goto KEEP;
	}
	//GET
	if ((p[0] == 'G') && (p[1] == 'E') && (p[2] == 'T')) {
		// request found
		counters.increment(0);
		sessions.lookup_or_init(&key, &ts);
		logs.update(&ts, &key);
		goto KEEP;
	}

	// //POST
	// if ((p[0] == 'P') && (p[1] == 'O') && (p[2] == 'S') && (p[3] == 'T')) {
	// 	goto KEEP;
	// }
	// //PUT
	// if ((p[0] == 'P') && (p[1] == 'U') && (p[2] == 'T')) {
	// 	goto KEEP;
	// }
	// //DELETE
	// if ((p[0] == 'D') && (p[1] == 'E') && (p[2] == 'L') && (p[3] == 'E') && (p[4] == 'T') && (p[5] == 'E')) {
	// 	goto KEEP;
	// }
	// //HEAD
	// if ((p[0] == 'H') && (p[1] == 'E') && (p[2] == 'A') && (p[3] == 'D')) {
	// 	goto KEEP;
	// }

	goto DROP;

	//keep the packet and send it to userspace retruning -1
	KEEP:
	return -1;

	//drop the packet returning 0
	DROP:
	return 0;

}
