
## [Linux Socket Filtering aka BPF](https://www.kernel.org/doc/Documentation/networking/filter.txt)

BPF allows a user-space program to attach a filter onto any socket and allow or disallow certain types of data to come through the socket.

- Linux workflow: create filter code, send to kernel via **SO_ATTACH_FILTER** option, get checked by kernel, begin filtering

- Termination: normally filter is removed automatically when socket is closed; or original filter is removed when a new filter is attached to it; detach via **SO_DETACH_FILTER**

- **SO_LOCK_FILTER** option locks the filter attached to a socket. assures filter stays until socket is closed. useful in situations like:
    - set up socket, attach filter, lock it, drop privileges.
   

### Structures
```c
#include <linux/filter.h>
// each line of filter code is a struct sock_filter
struct sock_filter {	/* Filter block */
	__u16	code;   /* Actual filter code */
	__u8	jt;	/* Jump true */
	__u8	jf;	/* Jump false */
	__u32	k;      /* Generic multiuse field */
};

// a bpf program is a list of such filter codes
struct sock_fprog {			/* Required for SO_ATTACH_FILTER. */
	unsigned short		   len;	/* Number of filter blocks */
	struct sock_filter __user *filter;
};
```

### Example
```c
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
/* ... */

/* From the example above: tcpdump -i em1 port 22 -dd */
struct sock_filter code[] = {
	{ 0x28,  0,  0, 0x0000000c },
	{ 0x15,  0,  8, 0x000086dd },
	{ 0x30,  0,  0, 0x00000014 },
	{ 0x15,  2,  0, 0x00000084 },
	{ 0x15,  1,  0, 0x00000006 },
	{ 0x15,  0, 17, 0x00000011 },
	{ 0x28,  0,  0, 0x00000036 },
	{ 0x15, 14,  0, 0x00000016 },
	{ 0x28,  0,  0, 0x00000038 },
	{ 0x15, 12, 13, 0x00000016 },
	{ 0x15,  0, 12, 0x00000800 },
	{ 0x30,  0,  0, 0x00000017 },
	{ 0x15,  2,  0, 0x00000084 },
	{ 0x15,  1,  0, 0x00000006 },
	{ 0x15,  0,  8, 0x00000011 },
	{ 0x28,  0,  0, 0x00000014 },
	{ 0x45,  6,  0, 0x00001fff },
	{ 0xb1,  0,  0, 0x0000000e },
	{ 0x48,  0,  0, 0x0000000e },
	{ 0x15,  2,  0, 0x00000016 },
	{ 0x48,  0,  0, 0x00000010 },
	{ 0x15,  0,  1, 0x00000016 },
	{ 0x06,  0,  0, 0x0000ffff },
	{ 0x06,  0,  0, 0x00000000 },
};

struct sock_fprog bpf = {
	.len = ARRAY_SIZE(code),
	.filter = code,
};

sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
if (sock < 0)
	/* ... bail out ... */

ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
if (ret < 0)
	/* ... bail out ... */

/* ... */
close(sock);
```

Summary:
```c
setsockopt(sockfd, SOL_SOCKET, SO_ATTACH_FILTER, &val, sizeof(val));
setsockopt(sockfd, SOL_SOCKET, SO_DETACH_FILTER, &val, sizeof(val));
setsockopt(sockfd, SOL_SOCKET, SO_LOCK_FILTER,   &val, sizeof(val));
```

### BPF assembly
#### Architecture
| Element | Description |
| :-----: | :---------: |
| A | 32 bit wide accumulator |
| X | 32 bit wide X register |
| M\[\] | 16 x 32 bit wide misc register |

#### Program Instruction
```
op:16, jt:8, jf:8, k:32
```
- 16 bits opcodes
- 8 bits jump targets for "jump if true" and "jump if false"
- 32 bits misc argument

- operations as usual; load, store, branch/jmp, arithmetics, A/X copying and return 
- addressing modes for register, 

**Example** 
- ARP packets:  

```
ldh [12]
jne #0x806, drop
ret #-1
drop: ret #0
```

- IPv4 TCP packets:

```
ldh [12]            # load half-word (2 bytes) starting from the 13th byte in the packet into A
jne #0x800, drop    # jump to drop if A != 0x800 ()
ldb [23]            # load a word (4 bytes) starting from the 24th byte in the packet into A
jneq #6, drop       # jump to drop if A != 6
ret #-1             # return -1
drop: ret #0        # return 0
```

**Example assembler output** for ARP packet filter
```shell
$ ./bpf_asm foo
```
```
4,40 0 0 12,21 0 1 2054,6 0 0 4294967295,6 0 0 0,
```

or in C-like output:
```shell
$ ./bpf_asm -c foo
```
```
{ 0x28,  0,  0, 0x0000000c },
{ 0x15,  0,  1, 0x00000806 },
{ 0x06,  0,  0, 0xffffffff },
{ 0x06,  0,  0, 0000000000 },
```

[**BPF instruction opcodes**](https://github.com/torvalds/linux/blob/master/include/uapi/linux/bpf_common.h)  
**Example C code** for ARP packets filter
```c
struct sock_filter code[] = {
    { BPF_LD | BPF_H | BPF_ABS, 0, 0, 12 },
    { BPF_JMP | BPF_JEQ, 0, 1, 0x806 },
    { BPF_RET, 0, 0, -1 },
    { BPF_RET, 0, 0, 0 }
}
```

**\[Follow up\]** Experiment with BPF c code
