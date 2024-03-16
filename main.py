#!/usr/bin/python
import os
import shutil
from itertools import count
from sys import argv as args
from subprocess import Popen, PIPE
SHARE_DIR_PATH = "/home//.local/share/cptool"
TEMPLATE_FILEPATH = os.path.join(SHARE_DIR_PATH, "template.cpp")
PROG_FILENAME = "main.cpp"
BIN_FILENAME = "main"
BUILD_CMD = "g++ {} -o {} -std=c++17 -O2 -Wall".format(PROG_FILENAME, BIN_FILENAME)
if len(args) <= 1:
    print("Subcommand required.")
    exit(1)
match args[1]:
    case "new":
        if len(args) <= 2:
            print("Name required.")
            exit(1)
        name = args[2]
        if os.path.exists(name):
            print("Name taken.")
            exit(1)
        os.mkdir(name)
        shutil.copy(TEMPLATE_FILEPATH, os.path.join(name, PROG_FILENAME))
    case "build":
        if os.system(BUILD_CMD):
            print("Compiler error.")
            exit(1)
    case "test":
        ok = False
        if os.path.isfile(BIN_FILENAME):
            for i in count(1):
                inp_filename = "be{}.txt".format(i)
                outp_filename = "ki{}.txt".format(i)
                if not (os.path.isfile(inp_filename) and os.path.isfile(outp_filename)):
                    break
                ok = ac = True
                print("{}. ".format(i), end="")
                with open(inp_filename, "rb") as f:
                    inp_content = f.read()
                with open(outp_filename) as f:
                    outp_lines = f.read().strip().split('\n')
                p = Popen([ "./{}".format(BIN_FILENAME) ], stdin=PIPE, stdout=PIPE, stderr=PIPE)
                actual_lines = p.communicate(input=inp_content)[0].decode().strip().split('\n')
                if len(actual_lines) == len(outp_lines):
                    for i in range(len(actual_lines)):
                        if actual_lines[i].strip() != outp_lines[i].strip():
                            ac = False
                            break
                else:
                    ac = False
                print("AC" if ac else "WA")
        if not ok:
            print("Testing error.")
            exit(1)
    case _:
        print("Invalid subcommand.")
        exit(1)
print("OK")
exit(0)

