## BPF Socket Filtering Demo
This demo uses BPF as pure socket filter to block udp packets.

### Description
demo-client sends arbitrary user supplied messages in UDP datagrams to demo-server.

demo-server accepts and prints received messages.
A BPF for udp will be installed onto the socket when demo-server receives a "block" message. Any further communication from the demo-client will be filtered out.
