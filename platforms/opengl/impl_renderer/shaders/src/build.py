#!env python

import os
import subprocess

target_files = os.listdir("./targets")

for file in target_files:
    print("building " + file + "...")
    command = str.format("m4 ./targets/{0} > ../{0}", file)
    subprocess.call(command, shell=True)
    print(file + " build finish.")
