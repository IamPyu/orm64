#!/bin/sh

if [[ ! -d $MESON_SOURCE_ROOT ]]; then
  echo "Testing ON"
  MESON_SOURCE_ROOT="$(pwd)"
fi

mandir="$MESON_SOURCE_ROOT/man/man/man1"
mkdir -p "$mandir"

doc(){
	ronn "$MESON_SOURCE_ROOT/man/$1.ronn" > "$mandir/$1.1"
}

doc orm64
doc orm64util
doc orm64Api
