import subprocess
import os


os.chdir(os.path.dirname(os.path.abspath(__file__)))

gcc = "C:\\MinGW\\bin\\gcc.exe"

portable_library = "-LC:\\MinGW\\lib -IC:\\MinGW\\include"
library = "-LC:\\msys64\\mingw64\\lib -IC:\\msys64\\mingw64\\include"
dll = "-fPIC -shared -DSDK1_EXPORTS -Wl,--out-implib,libSDK1.a"





subprocess.run(f"gcc {dll} -Wall -Werror -Wpedantic src/*.c -o libSDK1.dll -Iinclude -lSDL3 -lSDL3_image -lSDL3_ttf {library}", shell = True)
#subprocess.run(f"{gcc} {dll} -Wall -Werror -Wpedantic src/*.c -o libSDK1.dll -Iinclude -lSDL3 -lSDL3_image -lSDL3_ttf {portable_library}", shell = True)

