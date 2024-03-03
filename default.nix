with import <nixpkgs> {}; stdenv.mkDerivation {
  name = "orm64";
  pname = "orm64";
  src = ./.;
  nativeBuildInputs = [ pkg-config python3 meson ninja xxd ];
  buildInputs = [
    raylib
    luajit
    libedit
    git
  ];

  buildPhase = "meson setup .. --reconfigure && meson compile";
  installPhase = "meson install";

  meta = {
    homepage = "https://gitlab.com/IamPyu/orm64";
    description = "Orm64 System";
  };
}
