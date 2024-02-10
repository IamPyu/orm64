#!/usr/bin/env sh
echo '#ifndef _RES_H' > src/res.h
echo '#define _RES_H' >> src/res.h
echo $(xxd -i src/default.lua) >> src/res.h
echo $(xxd -i src/doc/help.md) >> src/res.h
echo $(xxd -i src/doc/api.md) >> src/res.h
echo '#endif' >> src/res.h

CC='clang'
CFLAGS+='-Wall -std=gnu18'
CFLAGS+=" $(pkg-config --libs --cflags libedit luajit ncurses raylib gtk4)"

SRC="$(find src -name "*.c")"
OUT='bin/orm64'

mkdir -p bin
$CC $CFLAGS $SRC -o $OUT

if [[ $1 -eq 1 && $? -eq 0 ]]; then
    $OUT
else
    echo 'Not running, $1 is not equal to 1 or build failed.'
fi