{
  pkgs ? import ./pkgs.nix,
  pythonPath ? "python27",
  linuxPath ? "linuxPackages_4_17"
}:
  with pkgs;
  let
    python = lib.getAttrFromPath (lib.splitString "." pythonPath) pkgs;
    linux = lib.getAttrFromPath (lib.splitString "." linuxPath) pkgs;
  in
    python.pkgs.buildPythonApplication {
      pname = "bcc-demo";
      version = "0.0.1";
      src = lib.cleanSource ./.;
      buildInputs = [
        linuxHeaders
      ];
      propagatedBuildInputs =
        [
          linux.bcc
        ] ++ (with python.pkgs; [
          whisper
          bottle
          pyroute2
        ]);
    }
