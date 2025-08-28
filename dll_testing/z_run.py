import os
import subprocess
os.chdir(os.path.dirname(os.path.abspath(__file__)))

SDK = "-lSDK1 -ISDK/include -LSDK/lib"
SDL = "-lSDL3 -lSDL3_image -lSDL3_ttf -LC:\\msys64\\mingw64\\lib -IC:\\msys64\\mingw64\\include"
 
subprocess.run(f"gcc -o test.exe src/*.c {SDK} {SDL} -Iinclude && test", shell=True)