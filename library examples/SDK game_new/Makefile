
GCC = gcc


INCLUDE = -IC:\\msys64\\ucrt64\\include -Iinclude -ISDK1/include -ISDK1/include/SDK1/entity -ISDK1/include/SDK1/sprite
LIB = -LC:\\msys64\\ucrt64\\lib -LSDK1/lib
LINK =  -lMemTrack -lSDL3 -lSDL3_image -lSDL3_ttf
SRC = src/*.c


FLAGS = -Wall -Werror -Wpedantic 
OPT = -O2 -march=native 
OUTPUT = game.exe



default: debug_build run
opt: opt_build run

debug_build: 
	@${GCC} ${SRC} -o ${OUTPUT} -Iinclude ${INCLUDE} -DTRACK_ALLOCATIONS -lSDK1_debug ${LINK} ${LIB} ${FLAGS}  

opt_build: 
	@${GCC} ${SRC} -o ${OUTPUT} -Iinclude ${INCLUDE}-lSDK1 ${LINK} ${LIB} ${FLAGS}  

run:
	@${OUTPUT}
