mandir=${MESON_INSTALL_PREFIX}/share/man
mkdir -p "${mandir}"

doc(){
	out="${MESON_SOURCE_ROOT}/res/${1}.1"
	pandoc "${MESON_SOURCE_ROOT}/res/${1}.md" -o $out
	mv $out $mandir
}

doc orm64

