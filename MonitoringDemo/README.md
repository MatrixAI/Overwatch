# Monitoring/BCC Demo

Initial experiements with working on BCC.

One problem is the development environment. BCC relies on the kernel version. So this is an externally specified detail that cannot be isolated within the shell.nix or default.nix.

Therefore, we have 3 things:

```
pythonPath
linuxPath
```

In order to ensure we are getting the right linux kernel module, we need to match the nixpkgs of the host environment. The `pkgs.nix` therefore just imports `import <nixpkgs {}`. This basically acquires the nixpkgs of the host. Therefore not all hosts will support it. Even with the same package set, you need to make sure we are getting the right kernel version. Otherwise you're not going to work on the same kernel. To do this, we need to set the `linuxPath`.

Later when deploying the application, make sure to wrap the `$LD_LIBRARY_PATH` for any output executables using the `makeWrapper`.

https://nixos.wiki/wiki/Linux_Kernel#Developing_Kernel_Modules
