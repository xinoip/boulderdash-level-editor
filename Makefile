OBJS = *.c ./*/*.c
CC = gcc
COMPILER_FLAGS = -Wall
LINKER_FLAGS = ./libs/libSDL2.so ./libs/libSDL2_image.so ./libs/libSDL2_ttf.so ./libs/libfreetype.so -L. `./sdl2-config --static-libs`

LD_LIBRARY_PATH = ./
export LD_LIBRARY_PATH

OBJ_NAME = app
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) | ./app LevelName 150 10 68 68
