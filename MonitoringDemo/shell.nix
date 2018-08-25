{
  pkgs ? import ./pkgs.nix,
  pythonPath ? "python27",
  linuxPath ? "linuxPackages_4_17"
}:
  with pkgs;
  let
    python = lib.getAttrFromPath (lib.splitString "." pythonPath) pkgs;
    linux = lib.getAttrFromPath (lib.splitString "." linuxPath) pkgs;
    drv = import ./default.nix { inherit pkgs pythonPath linuxPath; };
  in
    drv.overrideAttrs (attrs: {
      src = null;
      shellHook = ''
        echo 'Entering ${attrs.pname}'

        if [[ $EUID -ne 0 ]]; then
          echo "Run nix-shell with root permissions to run BPF code"
        fi

        set -v

        LD_LIBRARY_PATH="${lib.makeLibraryPath [ linux.bcc ] }:$LD_LIBRARY_PATH";

        C_INCLUDE_PATH="${lib.makeSearchPathOutput "dev" "include" drv.buildInputs}"

        # extra pip packages
        unset SOURCE_DATE_EPOCH
        export PIP_PREFIX="$(pwd)/pip_packages"
        PIP_INSTALL_DIR="$PIP_PREFIX/lib/python${python.majorVersion}/site-packages"
        export PYTHONPATH="$PIP_INSTALL_DIR:$PYTHONPATH"
        export PATH="$PIP_PREFIX/bin:$PATH"
        mkdir --parents "$PIP_INSTALL_DIR"
        pip install --editable .

        set +v
      '';
    })
