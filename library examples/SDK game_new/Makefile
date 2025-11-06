
CC = gcc
OUT = game.exe
SRC = src/*.c 
INCLUDE = -IC:\\msys64\\mingw64\\include -ISDK1/include -Iinclude
LINK = -lSDK1 -lSDL3 -lSDL3_image -lSDL3_ttf
LIBRARY = -LC:\\msys64\\mingw64\\lib -LSDK1/lib
ERROR = -Wall -Wpedantic #-Werror 

default: build run

build:

	${CC} -o ${OUT} ${SRC} ${INCLUDE} ${LINK} ${LIBRARY} ${ERROR}

run:

	${OUT}