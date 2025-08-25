import subprocess
library = "-LC:\\msys64\\mingw64\\lib -IC:\\msys64\\mingw64\\include"
src = "src/time.c src/display.c"

subprocess.run(f"gcc -Wall -Werror -Wpedantic test.c {src} -o SDK1 -Iinclude -lSDL3 -lSDL3_image {library} && SDK1", shell = True)

