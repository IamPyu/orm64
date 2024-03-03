#!/bin/sh
echo "$MESON_SOURCE_ROOT"

echo '#ifndef _RES_H' > src/res.h
echo '#define _RES_H' >> src/res.h
echo $(xxd -i src/default.lua) >> src/res.h
echo $(xxd -i src/doc/help.md) >> src/res.h
echo $(xxd -i src/doc/api.md) >> src/res.h
echo '#endif' >> src/res.h
