#!/bin/sh
mandir=${MESON_INSTALL_PREFIX}/share/man
mkdir -p "${mandir}"

doc(){
	out="${MESON_SOURCE_ROOT}/res/${1}.1"
	pandoc "${MESON_SOURCE_ROOT}/res/${1}.md" -o $out
	gunzip $out

	if [[ $? -eq 0 ]]; then
		mv "${MESON_SOURCE_ROOT}/res/${1}.1" $mandir
		rm -rf $out
	else
		mv $out $mandir
	fi
}

doc orm64

