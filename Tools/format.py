import subprocess

subprocess.call("..\\Dependencies\\AStyle\\AStyle.exe --style=allman --recursive -n ..\\Source\\*.cpp ..\\Source\\*.h ..\\Source\\.inl", shell=True)
subprocess.call("..\\Dependencies\\AStyle\\AStyle.exe --style=allman --recursive -n ..\\..\\hect\\Engine\\*.cpp ..\\..\\hect\\Engine\\*.h ..\\..\\hect\\Engine\\.inl", shell=True)
subprocess.call("..\\Dependencies\\AStyle\\AStyle.exe --style=allman --recursive -n ..\\..\\hect\\Tests\\*.cpp ..\\..\\hect\\Tests\\*.h ..\\..\\hect\\Tests\\.inl", shell=True)