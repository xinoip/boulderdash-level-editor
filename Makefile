OBJS = *.c ./*/*.c
CC = gcc
COMPILER_FLAGS = -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
#-lSDL2_ttf -lSDL2_mixer

OBJ_NAME = app
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) | ./app LevelName 150 10 68 68
