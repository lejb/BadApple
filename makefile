#OBJS specifies which files to compile as part of the project 
OBJS = main.cpp

#CC specifies which compiler we're using 
CC = clang++

#INCLUDE specifies the folder for header files we need
INCLUDE = -I/usr/include/SDL2

#LIBRARY specifies the folder of other libraries
LIBRARY = -L/usr/lib/

#COMPILER_FLAGS specifies the additional compilation options we're using 
COMPILER_FLAGS = -Wl,--allow-shlib-undefined

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lrt

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = main

#This is the target that compiles our executable 
all : $(OBJS) 
	$(CC) -o $(OBJ_NAME) $(INCLUDE) $(LIBRARY) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) 
