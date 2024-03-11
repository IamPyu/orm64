#!/usr/bin/env python3
import pathlib
import os

root = os.getenv("MESON_SOURCE_ROOT")
prefix = os.getenv("MESON_INSTALL_PREFIX")

os.system(f"mkdir -p {prefix}/share/man/man1")
for p in pathlib.Path(root+"/man").glob("*.1"):
    os.system(f"cp {p.__str__()} {prefix}/share/man/man1")
