import subprocess
subprocess.run("gcc -Wall -Werror -Wpedantic test.c -o SDK1 -Iinclude -lSDL3 -lSDL3_image -LC:\\msys64\\mingw64\\lib -IC:\\msys64\\mingw64\\include && SDK1", shell = True)