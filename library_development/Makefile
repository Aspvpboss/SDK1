
GCC = gcc
#GCC = gcc

INCLUDE = -Iinclude -IC:\\msys64\\mingw64\\include
LIB = -LC:\\msys64\\mingw64\\lib 
LINK = -lSDL3 -lSDL3_image -lSDL3_ttf -lMemTrack
SRC_LIB = src/*.c


FLAGS = -Wall -Werror -Wpedantic -pedantic
OPT = -O2 -march=native -flto 
OUTPUT = out.exe

DLL_FLAGS = -fPIC -shared  -Wl,--out-implib,libSDK1.a
DLL_OUTPUT = libSDK1.dll

default: build run


build_lib:
	@${GCC} ${OPT} ${SRC_LIB} -o ${DLL_OUTPUT} -DDLL_EXPORTS ${DLL_FLAGS} ${INCLUDE} ${FLAGS} ${LIB} ${LINK}

build: 
	@${GCC} ${SRC_LIB} -o ${OUTPUT} -DSTATIC_LINK ${INCLUDE} ${LINK} ${LIB} ${FLAGS}  

run:
	@${OUTPUT}

