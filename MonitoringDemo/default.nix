{
  pkgs ? import ./pkgs.nix,
  pythonPath ? "python27"
}:
  with pkgs;
  let
    python = lib.getAttrFromPath (lib.splitString "." pythonPath) pkgs;
  in
    python.pkgs.buildPythonApplication {
      pname = "bcc-demo";
      version = "0.0.1";
      src = lib.cleanSource ./.;
      buildInputs = [
        linuxPackages_4_17.bcc
      ] ++ (with python.pkgs; [
        whisper
      ]);
      LD_LIBRARY_PATH = lib.makeLibraryPath [ linuxPackages_4_17.bcc ];
    }
