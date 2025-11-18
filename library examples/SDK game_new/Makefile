
CC = gcc
OUT = game.exe
SRC = src/*.c 
INCLUDE = -IC:\\msys64\\mingw64\\include -ISDK1/include -Iinclude
LINK =  -lSDL3 -lSDL3_image -lSDL3_ttf -lMemTrack
LIBRARY = -LC:\\msys64\\mingw64\\lib -LSDK1/lib
ERROR = -Wall -Wpedantic -Werror 

default: debug_build run

opt: opt_build run

debug_build:

	@${CC} -o ${OUT} ${SRC} ${INCLUDE} -lSDK1_debug ${LINK} ${LIBRARY} ${ERROR} -DTRACK_ALLOCATIONS

opt_build:

	@${CC} -o ${OUT} ${SRC} ${INCLUDE} -lSDK1 ${LINK} ${LIBRARY} ${ERROR} -O3 -march=native

run:

	@${OUT}