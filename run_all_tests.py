import os
import subprocess

def execute(dir, exe, args=""):
    if os.path.exists(dir):
        subprocess.call("cd " + dir + " & " + exe + " " + args, shell=True)

execute("Build\\Windows\\Bin\\Debug\\x64", "HectUnitTests.exe")
execute("Build\\Windows\\Bin\\Debug\\x64", "HectSystemTests.exe", "--config SystemTests.config")

input("Press any key to continue")
