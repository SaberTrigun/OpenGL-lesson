COMPILE=g++
PATHLIB=-L ./lib
HEADERS=-lglfw -lGL -ldl -lX11 -lpthread -lXrandr -lXi 
SRC=gl.cpp glad.c stb_image.cpp
EXE=bin_gl
all:
	$(COMPILE) $(SRC) -o $(EXE) $(PATHLIB) $(HEADERS)
