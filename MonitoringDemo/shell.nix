{
  pkgs ? import ./pkgs.nix,
  pythonPath ? "python27"
}:
  with pkgs;
  let
    python = lib.getAttrFromPath (lib.splitString "." pythonPath) pkgs;
    drv = import ./default.nix { inherit pkgs pythonPath; };
  in
    drv.overrideAttrs (attrs: {
      src = null;
      shellHook = ''
        echo 'Entering ${attrs.pname}'

        if [[ $EUID -ne 0 ]]; then
          echo "nix-shell must be run as Root to use BPF"
        fi

        set -v

        LD_LIBRARY_PATH="${linuxPackages_4_17.bcc}/lib:$LD_LIBRARY_PATH"

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
