# \[WIP\] [Linux Socket Filtering with BPF - Part 2](https://www.kernel.org/doc/Documentation/networking/filter.txt)
## eBPF
Extended BPF with more capabilities.  

### Program Types
`linux/bpf.h` header contains following bpf program types.
```c
enum bpf_prog_type {
	BPF_PROG_TYPE_UNSPEC,            
	BPF_PROG_TYPE_SOCKET_FILTER,     # Socket filtering as used in demo
	BPF_PROG_TYPE_KPROBE,            # krpobe & kretprobes
	BPF_PROG_TYPE_SCHED_CLS,         
	BPF_PROG_TYPE_SCHED_ACT,
	BPF_PROG_TYPE_TRACEPOINT,        # Tracepoint
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

### Data Storage
eBPF maps available in different data structures, array, hashmap, etc.

### Writing program with eBPF
### Problem
- `bpf(...)` is in manpages but not present in `<linux/bpf.h>` or `<linux/bpf_common.h>`
- linker reports `bpf(...)` undefined
- /dev/bpf device does not exist

### Workaround
Based on [bcc](https://github.com/iovisor/bcc/blob/master/src/cc/libbpf.c)'s way of calling bpf, `syscall(__NR_bpf, ...)` should be used instead of direct `bpf(...)` calls
