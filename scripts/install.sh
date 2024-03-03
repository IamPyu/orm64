#!/bin/sh

DATADIR=$HOME/.config/orm64
mkdir -p $DATADIR
cp -r $MESON_SOURCE_ROOT/default/* $DATADIR

echo "" > /dev/null 
