import os
import subprocess
os.chdir(os.path.dirname(os.path.abspath(__file__)))


gcc = "C:\\MinGW\\bin\\gcc.exe"
SDK = "-lSDK1 -ISDK1/include -LSDK1/lib"
SDL = "-lSDL3 -lSDL3_image -lSDL3_ttf -LC:\\msys64\\mingw64\\lib -IC:\\msys64\\mingw64\\include"
portable_SDL = "-lSDL3 -lSDL3_image -lSDL3_ttf -LC:\\MinGW\\lib -IC:\\MinGW\\include"
 
subprocess.run(f"gcc -o test.exe src/*.c {SDK} {SDL} -Iinclude && test", shell=True)
#subprocess.run(f"{gcc} -o test.exe src/*.c {SDK} {portable_SDL} -Iinclude && test", shell=True)
