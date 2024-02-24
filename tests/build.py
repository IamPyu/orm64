import os
import pathlib

def main(p):
  for path in pathlib.Path(p).glob("*.c"):
    path = path.__str__()
    to = path.removesuffix(".c")
    failure = os.system(f"clang {path} -o {to}.out -lc -lormlib")
    if not failure:
      print(f"Running test: {to}")
      os.system(f"./{to}")
    else:
      print(f"Build for test '{to}' failed!")

main("./tests")
main("./")