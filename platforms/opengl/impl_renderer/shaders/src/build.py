#!env python

import os
import subprocess
import sys

base_path = sys.argv[1]
target_files = os.listdir(os.path.join(base_path, "./targets"))

for file in target_files:
    print("building " + file + "...")
    source = os.path.join(base_path, "./targets/" + file)
    dst = os.path.join(base_path, "../" + file)
    command = str.format("m4 {0} -I {1} > {2}", source, base_path, dst)
    subprocess.call(command, shell=True)
    print(file + " build finish.")
