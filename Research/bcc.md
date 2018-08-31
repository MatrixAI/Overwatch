# [BCC](https://github.com/iovisor/bcc)
## tcplife example structure
May need to refer to this later when we actually generate Overwatch Monitors
1. generate data structures
  - ipv4 records, ipv6 records, user records? and output table
2. setup either kprobes (linux 4.14 and older) or tracepoint (linux 4.16(4.15) and newer)
  - kprobe: find the kernel function to probe, create `kprobe__function_name(struct pt_regs *ctx, args...)`
  - tracepoints:

## BPF C Events Tracing
### [Comparison](https://nanxiao.me/en/brief-differences-between-tracepoints-kprobes-uprobes-usdt/)

||Static|Dynamic|Kernel Tracing|Userland Tracing|
|:-:|:-:|:-:|:-:|:-:|
|Tracepoints|✔||✔||
|Kprobes||✔|✔||
|Uprobes||✔||✔|
|USDT|✔|||✔|
### [kprobes and kretprobes](https://www.kernel.org/doc/Documentation/kprobes.txt)
Attached to any kernel function and will be triggered on call or return.

### [Tracepoints](https://www.kernel.org/doc/Documentation/trace/tracepoints.txt)
Hooks to function calls

### [uprobes and uretprobes](https://www.kernel.org/doc/Documentation/trace/uprobetracer.txt)

### USDT probes

### Raw Tracepoints

### perf

###

##
