#!/usr/bin/env sh

# src/res.h
echo '#ifndef _RES_H' > src/res.h
echo '#define _RES_H' >> src/res.h
echo $(xxd -i src/default.lua) >> src/res.h
echo $(xxd -i src/doc/help.md) >> src/res.h
echo $(xxd -i src/doc/api.md) >> src/res.h
echo '#endif' >> src/res.h

# preinstalled programs for orm64
mkdir -p $HOME/.config/orm64/software
cp -r apps/* $HOME/.config/orm64/software 