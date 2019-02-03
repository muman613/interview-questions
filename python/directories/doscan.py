"""
Scan a directory, printing each file and recursing into each sub-directory.

By Michael Uman December 4th, 2018
"""

import os
import sys

def recurse_directory(path: str):
    """
    Traverse the directory tree using os.scandir()
    :param path:
    :return:
    """

    if os.path.exists(path):
        try:
            with os.scandir(path) as it:
                for entry in it:
                    if not entry.name.startswith("."):
                        if entry.is_file():
                            print("path = {} name = {}".format(path + os.path.sep, entry.name))
                        elif entry.is_dir():
                            recurse_directory(entry.path)
        except OSError:
            return

    return


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else "/tmp"

    recurse_directory(path)


if __name__ == "__main__":
    main()

