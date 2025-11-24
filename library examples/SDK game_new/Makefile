
# GCC = gcc


# INCLUDE = -IC:\\msys64\\ucrt64\\include -Iinclude -ISDK1/include
# LIB = -LC:\\msys64\\ucrt64\\lib -LSDK1/lib
# LINK = -lMemTrack -lSDL3 -lSDL3_image -lSDL3_ttf
# SRC = src/*.c


# FLAGS = -Wall -Werror -Wpedantic 
# OPT = -O2 -march=native 
# OUTPUT = game.exe



# default: debug_build run
# opt: opt_build run

# debug_build: 
# 	${GCC} ${SRC} -o ${OUTPUT} -Iinclude ${INCLUDE} ${LIB} -DTRACK_ALLOCATIONS -lSDK1_debug ${LINK} ${FLAGS}  

# opt_build: 
# 	${GCC} ${SRC} -o ${OUTPUT} -Iinclude ${INCLUDE} ${LIB} -lSDK1 ${LINK} ${FLAGS}  

# run:
# 	@${OUTPUT}



# Makefile for SDK1 game project

# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -ISDK1/include -Wall -Werror -Wpedantic
DEBUG_FLAGS = -DTRACK_ALLOCATIONS
OPT_FLAGS = -O2

# Library paths
LIB_PATHS = -LSDK1/lib -LC:\msys64\ucrt64\lib
LIBS_DEBUG = -lSDK1_debug -lMemTrack -lSDL3 -lSDL3_image -lSDL3_ttf
LIBS_OPT = -lSDK1 -lMemTrack -lSDL3 -lSDL3_image -lSDL3_ttf

# Source and object files
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = game.exe

# Default build (debug)
all: debug_build

# Debug build
debug_build: CFLAGS += $(DEBUG_FLAGS)
debug_build: $(OBJS)
	$(CC) $(OBJS) $(LIB_PATHS) $(LIBS_DEBUG) -o $(TARGET)

# Optimized build
opt_build: CFLAGS += $(OPT_FLAGS)
opt_build: $(OBJS)
	$(CC) $(OBJS) $(LIB_PATHS) $(LIBS_OPT) -o $(TARGET)

# Compile .c to .o
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f src/*.o $(TARGET)