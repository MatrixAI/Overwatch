{
  pkgs ? import ./pkgs.nix,
  haskellPath ? "ghc822"
}:
  with pkgs;
  let
    haskellPackages = lib.getAttrFromPath (lib.splitString "." haskellPath) haskell.packages;
    drv = haskellPackages.callPackage (import ./cabal.nix) {};
  in
    haskell.lib.buildStrictly (
      drv.overrideAttrs (attrs: {
        src = lib.cleanSourceWith {
          filter = (path: type:
            ! (builtins.any
              (r: (builtins.match r (builtins.baseNameOf path)) != null)
              [
                "dist"
                "\.env"
              ])
          );
          src = lib.cleanSource attrs.src;
          buildInputs = attrs.buildInputs ++ (with linuxPackages; [ bcc ]);
        };
      })
    )
