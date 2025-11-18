
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
DEBUG_DLL_OUTPUT = libSDK1_debug.dll


default: debug_build run

opt: opt_build run


build_lib: opt_build_lib
	@${GCC} ${OPT} ${SRC_LIB} -o ${DEBUG_DLL_OUTPUT} -DTRACK_ALLOCATIONS -DDLL_EXPORTS ${DLL_FLAGS} ${INCLUDE} ${FLAGS} ${LIB} ${LINK}

opt_build_lib:
	@${GCC} ${OPT} ${SRC_LIB} -o ${DLL_OUTPUT} -DDLL_EXPORTS ${DLL_FLAGS} ${INCLUDE} ${FLAGS} ${LIB} ${LINK}

debug_build: build_lib
	@${GCC} main.c -o ${OUTPUT} -Iinclude ${INCLUDE} -DTRACK_ALLOCATIONS -L. -lSDK1_debug ${LINK} ${LIB} ${FLAGS}  

opt_build: build_lib
	@${GCC} main.c -o ${OUTPUT} -Iinclude ${INCLUDE}  -L. -lSDK1 ${LINK} ${LIB} ${FLAGS}  

run:
	@${OUTPUT}

