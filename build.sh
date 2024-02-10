#!/usr/bin/env sh
echo '#ifndef _RES_H' > src/res.h
echo '#define _RES_H' >> src/res.h
echo $(xxd -i src/default.lua) >> src/res.h
echo $(xxd -i src/doc/help.md) >> src/res.h
echo $(xxd -i src/doc/api.md) >> src/res.h
echo '#endif' >> src/res.h

CC='clang'
CFLAGS+='-Wall -std=gnu18 '
CFLAGS+="$(pkg-config --libs --cflags libedit luajit ncurses raylib)"

SRC="$(find src -name "*.c")"
OUT='bin/orm64'

mkdir -p bin
$CC $CFLAGS $SRC -o $OUT

mkdir -p $HOME/.config/orm64/software
cp -r apps/* $HOME/.config/orm64/software 

if [[ $1 -eq 1 && $? -eq 0 ]]; then
    $OUT
else
    echo 'Not running, $1 is not equal to 1.'
fi
