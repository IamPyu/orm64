with import <nixpkgs> {}; stdenv.mkDerivation {
  name = "env";
  src = ./.;
  nativeBuildInputs = [ pkg-config python3 meson ninja xxd ];
  buildInputs = [
    raylib
    luajit
    libedit
    git
  ];

  buildPhase = "meson setup .. && meson compile";
  installPhase = "meson install";
}
