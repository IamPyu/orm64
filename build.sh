mkdir -p bin
rm -rf ./bin/*
meson setup bin .
meson configure $@
meson compile -C bin

if [[ $INSTALL -eq 1 ]]; then
	meson install -C bin
fi
