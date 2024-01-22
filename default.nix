with import <nixpkgs> {};

pkgs.mkShell {
  packages = with pkgs; [
    pkg-config
    luajit
    luarocks
    libiconv
  ];
}
