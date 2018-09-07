# \[WIP\] Http monitoring demo
Some notes when writing the demo for HTTP monitor using eBPF that tracks number of HTTP exchanges made and latency for each exchange.

## Reference [BCC HTTP Filter](https://github.com/iovisor/bcc/tree/master/examples/networking/http_filter)
This is more filtering than monitoring though.

1. Attach a BPF program as socket filter that tracks and stores all requests in a BPF Hashmap
  - (src_ip, src_port, dst_ip, dst_port) is used as key in the hashmap
  - timestamps as value in the hashmap, eBPF code only initialize to zero
  - non http packets are dropped
2. In userspace, parse http packets, match requests and responses with the key tuple above, print

### Thoughts
- The key tuple to keep track of sessions in hashmap seems nice
- Need to clear the map when a session ends, or simply overwrite when a new request from same key arrives. Later may be problematic on messy connections?
- Timing, can we do this in BPF code? Look for in-kernel helper function that does this and is callable from BPF socket filters.
  - Yes we can. [bpf_ktime_get_ns()](https://github.com/iovisor/bcc/blob/master/docs/reference_guide.md#3-bpf_ktime_get_ns)
- BPF is attached to the socket on creation. Means we need to wrap the socket syscall to inject BPF code?
  - No. According to observation from running http_filter example, the socket filter catches all packets on the interface rather than on a specific port. Need more investigation.
- Output to user space. `BPF_PERF_OUTPUT` maybe? [problem](#output-issue)

## HTTP Monitor
### Socket filter approach
#### Output issue
- For output to user space from BPF code, use `perf_submit_skb(void *, u32, void *, u32);` instead of `perf_submit(void *, void *, u32)`. First 2 args should be `skb` and `sizeof(skb)`. [Reference](https://github.com/iovisor/bcc/blob/6d85aca0e667320ae00d1b135ee093ff2cae3852/examples/networking/tc_perf_event.py#L42)
- Follow up on previous point. Getting `unknown func bpf_perf_event_output#25` problems. Perf output is not available in socket filter programs? only example doing this is the above reference but it has [other problems](#bpf-errors).
- Running the above reference on ubuntu with libbcc 0.7.0 gives no error. `perf_submit` and `perf_submit_skb` should be usable in socket filter programs.

#### BPF errors
- `AttributeError: 'BPF' object has no attribute 'get_syscall_fnname'`, `AttributeError: 'BPF' object has no attribute 'perf_buffer_poll'` and more!
- Looks like a version issue [bcc issue](https://github.com/iovisor/bcc/issues/1740)
- These are working on ubuntu bionic wth libbcc 0.7.0. NixOS package search only has bcc 0.5.0.

### Tracepoints/probes
