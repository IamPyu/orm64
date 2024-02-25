#!/bin/sh
DATADIR=~/.config/orm64
mkdir -p $DATADIR
cp -r $MESON_SOURCE_ROOT/default/* $DATADIR

python3 $MESON_SOURCE_ROOT/tests/build.py