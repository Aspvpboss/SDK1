
GCC = gcc
#GCC = gcc

INCLUDE = -IC:\\msys64\\mingw64\\include -Iinclude/SDK1 -Iinclude/SDK1/entity -Iinclude/SDK1/sprite
LIB = -LC:\\msys64\\mingw64\\lib 
LINK = -lSDL3 -lSDL3_image -lSDL3_ttf -lMemTrack
SRC_LIB = src/*.c src/sprite/*.c src/entity/*.c



FLAGS = -Wall -Werror -Wpedantic -pedantic
OPT = -O2 -march=native 
OUTPUT = out.exe

DLL_FLAGS = -fPIC -shared  -Wl,--out-implib,libSDK1.a
DLL_OUTPUT = libSDK1.dll

MEMTRACK_SETTING = -DTRACK_ALLOCATIONS

default: build run


build_lib:
	@${GCC} ${OPT} ${SRC_LIB} -o ${DLL_OUTPUT} ${MEMTRACK_SETTING} -DDLL_EXPORTS ${DLL_FLAGS} ${INCLUDE} ${FLAGS} ${LIB} ${LINK}

build: build_lib
	@${GCC} main.c -o ${OUTPUT} -Iinclude ${INCLUDE} ${MEMTRACK_SETTING} -L. -lSDK1 ${LINK} ${LIB} ${FLAGS}  

run:
	@${OUTPUT}

