#!/bin/sh
mandir="man/man"
mkdir -p "${MESON_SOURCE_ROOT}/${mandir}"

doc(){
	pandoc "${MESON_SOURCE_ROOT}/man/${1}.md" -o "${MESON_SOURCE_ROOT}/${mandir}/${1}.1"
}

doc orm64
