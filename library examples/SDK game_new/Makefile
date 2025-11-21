
GCC = gcc


INCLUDE = -IC:\\msys64\\mingw64\\include -Iinclude -ISDK1/include -ISDK1/include/SDK1/entity -ISDK1/include/SDK1/sprite
LIB = -LC:\\msys64\\mingw64\\lib -LSDK1/lib
LINK = -lSDL3 -lSDL3_image -lSDL3_ttf -lMemTrack
SRC = src/*.c


FLAGS = -Wall -Werror -Wpedantic 
OPT = -O2 -march=native 
OUTPUT = game.exe



default: debug_build run
opt: opt_build run

debug_build: 
	@${GCC} ${SRC} -o ${OUTPUT} -Iinclude ${INCLUDE} -DTRACK_ALLOCATIONS ${LINK} -lSDK1_debug ${LIB} ${FLAGS}  

opt_build: 
	@${GCC} ${SRC} -o ${OUTPUT} -Iinclude ${INCLUDE} ${LINK} -lSDK1 ${LIB} ${FLAGS}  

run:
	@${OUTPUT}
