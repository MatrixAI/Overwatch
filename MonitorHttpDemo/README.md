## HTTP monitor using eBPF
This project is a minimum demo of how eBPF can be used to monitor HTTP traffic.

### Depenencies
Either
```
nixpkgs 29cdfe021872dbb2e6a01f2f52a19737430a9a0e
bcc 0.7.0
python 3.6
```
or
```
nixpkgs-channels 4df3426f5a5e78cef4835897a43abd9e2a092b74
bcc 0.5.0
python 2.7
```
** Note: **
- `bottle` python package is used to run a http server.
- kernel update to `4.17.19` may be required to run `bcc 0.7.0`

### Usage
#### Basic
1. `sudo nix-shell`
  - `sudo` is required to run bcc
2. `python monitorHttp.py [-i <ifname>]`
  - `ifname` interface name to monitor, default to `lo`
  - prints start line of http request/response exchange
  - collected metrics (# of req/resp, latency for each exchange, logs) are shown on termination (via keyboardInterrupt)
3. `python httpServ.py [-h <host_ip>]` to run a http server on `<host_ip>:8080`. Default to `localhost`
4. `url <host_ip>:8080` to generate some http traffic for monitoring

#### Linux Network Namespace
1. `sudo ip netns add ns0`, create network namespace
2. `sudo ip netns exec ns0 nix-shell`, run `nix-shell` in network namespace
3. `python monitorHttp.py [-i <ifname>]` run monitor script
4. `sudo ip netns exec ns0 nix-shell` and `python httpServ.py [-h <host_ip>]` to run a http server in the network namespace
5. `sudo ip netns exec ns0 curl <host_ip>:8080` to send http request from within the namespace
