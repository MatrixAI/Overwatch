# Haskell libbcc bindings

This project creates haskell bindings on libbcc's c api in the same fashion as libbcc's python frontend.

The project structure is based on [Haskell-Demo](https://github.com/MatrixAI/Haskell-Demo).

## Environment
- Nixpkgs: `channels/nixos-18.09` `06fb0253afabb8cc7dc85db742e2de94a4d68ca0`
- Kernel packages: `pkgs.linuxPackages_4_18`
- BCC: `bcc-0.6.1`
- Not: NixOS `configuration.nix` has to be on the same nixpkgs as project `./pkgs.nix` to avoid errors where bcc cannot properly find correct version of development file
