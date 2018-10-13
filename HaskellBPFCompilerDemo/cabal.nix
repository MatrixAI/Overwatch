{ mkDerivation, base, clang, hpack, linuxHeaders, stdenv }:
mkDerivation {
  pname = "haskell-demo";
  version = "0.1.0.0";
  src = ./.;
  isLibrary = true;
  isExecutable = true;
  libraryHaskellDepends = [ base ];
  libraryToolDepends = [ clang hpack linuxHeaders ];
  executableHaskellDepends = [ base ];
  executableToolDepends = [ clang linuxHeaders ];
  testHaskellDepends = [ base ];
  testToolDepends = [ clang linuxHeaders ];
  preConfigure = "hpack";
  homepage = "https://github.com/MatrixAI/Haskell-Demo#readme";
  license = stdenv.lib.licenses.asl20;
}
