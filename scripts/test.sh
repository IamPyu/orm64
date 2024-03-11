nix-build -arg debug true -arg bloat false $@
sudo rm -rf ~/.config/orm64
mkdir -p ~/.config/orm64

sudo cp -r ./result/etc/orm64/default/* ~/.config/orm64
