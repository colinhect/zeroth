import os
from subprocess import call

def execute(path, args=""):
    if os.path.exists(path):
        call(path + " " + args, shell=True)

execute("Build\\Windows\\Bin\\Debug\\Win32\\HectUnitTests.exe")
execute("Build\\Windows\\Bin\\Debug\\x64\\HectUnitTests.exe")
execute("Build\\Windows\\Bin\\Release\\Win32\\HectUnitTests.exe")
execute("Build\\Windows\\Bin\\Release\\x64\\HectUnitTests.exe")

execute("Build\\Windows\\Bin\\Debug\\Win32\\HectSystemTests.exe", "--path ..\\hect\\Tests\\Assets")
execute("Build\\Windows\\Bin\\Debug\\x64\\HectSystemTests.exe", "--path ..\\hect\\Tests\\Assets")
execute("Build\\Windows\\Bin\\Release\\Win32\\HectSystemTests.exe", "--path ..\\hect\\Tests\\Assets")
execute("Build\\Windows\\Bin\\Release\\x64\\HectSystemTests.exe", "--path ..\\hect\\Tests\\Assets")

input("Press any key to continue")
