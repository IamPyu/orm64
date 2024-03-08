{debug ? false}:

let
  debugArg = if debug then "-Ddebug_install=true" else "-Ddebug_install=false";
in

with import <nixpkgs> {}; stdenv.mkDerivation {
  name = "orm64";
  pname = "orm64";
  src = ./.;
  nativeBuildInputs = [ pkg-config python3 meson ninja xxd pandoc ];
  buildInputs = [
    raylib
    luajit
    libedit
    git
  ];

  buildPhase = "meson setup .. --reconfigure && meson configure ${debugArg} && meson compile";
  installPhase = "meson install";
  
  meta = {
    homepage = "https://gitlab.com/IamPyu/orm64";
    description = "Orm64 System";
  };
}
