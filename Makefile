CC = g++
LANG_STD = -std=c++17
COMPILER_FLAGS = -Wall -Wfatal-errors
INCLUDE_PATH = -I"C:\libsdl\include"
SRC_FILES = ./src/*.cpp
LINKER_FLAGS = -L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2
OBJ_NAME = 3d-software-renderer.exe

build:
	$(CC) $(COMPILER_FLAGS) $(LANG_STD) $(INCLUDE_PATH) $(SRC_FILES) $(LINKER_FLAGS) -o $(OBJ_NAME)

run:
	$(OBJ_NAME)

clean:
	del $(OBJ_NAME)
