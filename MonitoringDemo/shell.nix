# Run as root otherwise BPF fails
{ pkgs ? import <nixpkgs> {} }:
  with pkgs;
  python27Packages.buildPythonApplication {
    name = "MonitoringDemo";
    buildInputs = with python27Packages; [ linuxPackages.bcc whisper ];
    shellHook = ''
      export LD_LIBRARY_PATH="${linuxPackages.bcc}/lib:$LD_LIBRARY_PATH"
      if [[ $EUID -ne 0 ]]; then
        echo "nix-shell must be run as Root to use BPF"
      fi
    '';
  }
