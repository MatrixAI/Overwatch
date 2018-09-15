# \[WIP\] Linux Tracing Tools
## References
- Linux Tracing Overview https://jvns.ca/blog/2017/07/05/linux-tracing-systems/  
- OpenTracing - https://research.google.com/archive/papers/dapper-2010-1.pdf  
- Choosing Tracer - http://www.brendangregg.com/blog/2015-07-08/choosing-a-linux-tracer.html  
- https://blog.yadutaf.fr/2017/07/28/tracing-a-packet-journey-using-linux-tracepoints-perf-ebpf/  
- http://www.brendangregg.com/blog/2015-09-22/bcc-linux-4.3-tracing.html
- http://www.brendangregg.com/perf.html

## Data Sources
### Probing
#### [kprobes](https://www.kernel.org/doc/Documentation/kprobes.txt)
Attached to any kernel function and will be triggered on call (kprobe) or return (kretprobe).
#### [uprobes](https://www.kernel.org/doc/Documentation/trace/uprobetracer.txt)
userspace c functions probing with 2 variants triggered on call or return similiarly.
### Tracing
#### [kernel tracepoints](https://www.kernel.org/doc/Documentation/trace/tracepoints.txt)
Static hooks to function calls available at `/sys/kernel/debug/tracing/events/`
#### USDT/dtrace
#### LTTng userspace tracing

### [A comparision of krobes, uprobes, tracepoints and USDT](https://nanxiao.me/en/brief-differences-between-tracepoints-kprobes-uprobes-usdt/)

||Static|Dynamic|Kernel Tracing|Userland Tracing|
|:-:|:-:|:-:|:-:|:-:|
|Tracepoints|✔||✔||
|Kprobes||✔|✔||
|Uprobes||✔||✔|
|USDT|✔|||✔|

## Data Collection Mechanism


## Frontends
