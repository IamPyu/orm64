#!/usr/bin/env bash
echo $(xxd -i src/default.lua) > src/res.h
echo $(xxd -i src/doc/help.md) >> src/res.h
echo $(xxd -i src/doc/api.md) >> src/res.h