#!/usr/bin/env sh
#sh configure.sh
#
#CC='clang'
#CFLAGS+="-Wall -std=gnu18 $(pkg-config --libs --cflags libedit luajit ncurses raylib)"
#
#SRC="$(find src -name "*.c")"
#OUT='bin/orm64'
#
#mkdir -p bin
#$CC $CFLAGS $SRC -o $OUT
#
mkdir -p bin
cd bin
cmake ..
cmake --build

if [[ $1 -eq 1 && $? -eq 0 ]]; then
    ./orm64
else
    echo 'Not running, $1 is not equal to 1.'
fi
