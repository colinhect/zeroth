import os
import sys
from subprocess import call

call("python ../hect/Tools/create_zip.py Deploy/Hect.data ../hect/Assets/Hect Hect", shell=True)
call("python ../hect/Tools/create_zip.py Deploy/Zeroth.data Assets", shell=True)