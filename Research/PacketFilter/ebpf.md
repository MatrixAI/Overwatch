# \[WIP\] [Linux Socket Filtering with BPF - Part 2](https://www.kernel.org/doc/Documentation/networking/filter.txt)
## eBPF
Extended BPF with more capabilities.  

Some references:  
[Unofficial eBPF specs from BCC devs](https://github.com/iovisor/bpf-docs/blob/master/eBPF.md)  
[Slides for BPF/eBPF talk by Suchakra Sharma](https://speakerdeck.com/tuxology/the-bsd-packet-filter)  
[Julia Evans's notes on eBPF](https://jvns.ca/blog/2017/06/28/notes-on-bpf---ebpf/)

### eBPF Programs
`linux/bpf.h` header contains following bpf program types.
```c
enum bpf_prog_type {
	BPF_PROG_TYPE_UNSPEC,            
	BPF_PROG_TYPE_SOCKET_FILTER,     
	BPF_PROG_TYPE_KPROBE,            
	BPF_PROG_TYPE_SCHED_CLS,         
	BPF_PROG_TYPE_SCHED_ACT,
	BPF_PROG_TYPE_TRACEPOINT,        
	BPF_PROG_TYPE_XDP,
	BPF_PROG_TYPE_PERF_EVENT,
	BPF_PROG_TYPE_CGROUP_SKB,
	BPF_PROG_TYPE_CGROUP_SOCK,
	BPF_PROG_TYPE_LWT_IN,
	BPF_PROG_TYPE_LWT_OUT,
	BPF_PROG_TYPE_LWT_XMIT,
	BPF_PROG_TYPE_SOCK_OPS,
	BPF_PROG_TYPE_SK_SKB,
	BPF_PROG_TYPE_CGROUP_DEVICE,
};
```

- More than a simple socket filter;
- Can tap into kernel fucntions and userland functions with probes;
- Can hook onto tracepoints;
- Some other program type such as security is mentioned in [Suchakra Sharma's slides](https://speakerdeck.com/tuxology/the-bsd-packet-filter) as well

### eBPF Events Tracing
eBPF can collect data from kprobes, uprobes, USDT probes, kernel tracepoints, etc.

### Data Storage
eBPF maps available in different data structures, array, hashmap, etc.

### Communication
eBPF map, ftrace, perf buffer

### Writing program with eBPF
#### Problem
The `bpf()` syscall does not exist in the `linux/bpf.h` header. Neither can linker link to it.

**Workaround**:  
Based on [bcc](https://github.com/iovisor/bcc/blob/master/src/cc/libbpf.c)'s way of calling bpf, `syscall(__NR_bpf, ...)` should be used instead of direct `bpf(...)` calls. Refer to [BPF internals]() document from bcc for more detail.
