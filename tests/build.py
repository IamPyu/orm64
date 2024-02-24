import os
import pathlib

for path in pathlib.Path("./").glob("*.c"):
    path = path.__str__()
    to = path.removesuffix(".c")
    os.system(f"clang {path} -o {to}.out -lc -lormlib")
    