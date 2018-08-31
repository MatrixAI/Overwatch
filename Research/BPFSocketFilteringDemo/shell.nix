{
  pkgs ? import <nixpkgs> {}
}:
  with pkgs;
  stdenv.mkDerivation {
    name = "bpf-socket-filtering-demo";
  }
