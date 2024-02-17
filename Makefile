CC:=clang
CFLAGS+=-Wall -std=c11
CFLAGS+=$(shell pkg-config --libs --cflags libedit luajit ncurses raylib)

SRC:=$(shell find src -name "*.c")
OUT:="bin/orm64"

.PHONY: build config
build:
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

config:
	echo '#ifndef _RES_H' > src/res.h
	echo '#define _RES_H' >> src/res.h
	echo $(xxd -i src/default.lua) >> src/res.h
	echo $(xxd -i src/doc/help.md) >> src/res.h
	echo $(xxd -i src/doc/api.md) >> src/res.h
	echo '#endif' >> src/res.h

	mkdir -p ~/.config/orm64/software
	cp -r apps/* ~/.config/orm64/softwaren

run: build
	$(OUT)
