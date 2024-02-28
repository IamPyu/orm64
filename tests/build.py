import os
import pathlib


def main(p):
    for path in pathlib.Path(p).glob("*.cpp"):
        path = path.__str__()
        to = path.removesuffix(".cpp")
        failure = os.system(f"clang++ {path} -o {to}.out -lc -lormlib")
        if not failure:
            print(f"Running test: {to}")
            os.system(f"./{to}")
        else:
            print(f"Build for test '{to}' failed!")


main("./tests")
main("./")

