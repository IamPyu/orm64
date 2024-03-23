#!/usr/bin/env python3
import pathlib
import os

root = os.getenv("MESON_SOURCE_ROOT")
prefix = os.getenv("MESON_INSTALL_PREFIX")

def setup_man(n):
    os.system(f"mkdir -p {prefix}/share/man/man{n}")
    for p in pathlib.Path(root+"/man").glob(f"*.{n}"):
        os.system(f"gzip -fk {p}")
        os.system(f"mv {p.__str__()}.gz {prefix}/share/man/man{n}")
    return 0

# See man(1) for information on how man pages are sorted. See groff_man(7) to learn how to write manpages.
setup_man("1") # General commands
setup_man("3") # Library functions
