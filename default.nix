{
  debug ? false,
  bloat ? true
}:

let
  debugArg = if debug then "-Ddebug_install=true" else "-Ddebug_install=false";
  bloatArg = if bloat then "-Denable_bloat=true" else "-Denable_bloat=false";
in

with import <nixpkgs> {}; stdenv.mkDerivation {
  name = "orm64";
  pname = "orm64";
  src = ./.;
  nativeBuildInputs = [ pkg-config python3 meson ninja xxd ronn ];
  buildInputs = [
    raylib
    luajit
    libedit
    git
    SDL2
    SDL2_net
  ];

  buildPhase = "meson setup .. --reconfigure && meson configure ${debugArg} ${bloatArg} && meson compile";
  installPhase = "meson install";
  
  meta = {
    homepage = "https://gitlab.com/IamPyu/orm64";
    description = "Orm64 System";
  };
}
