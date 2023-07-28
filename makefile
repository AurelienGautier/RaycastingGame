CXX = g++
EXEC = bin/prog
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)
SFML_LIBS = -lsfml-window -lsfml-system -lsfml-graphics

ifeq ($(OS), Windows_NT)
	SFML_INCLUDE = -I include
	SFML_LIB = -L lib
endif

ifeq ($(OS), Linux)
	SFML_INCLUDE = 
	SFML_LIB = 
endif

all : $(EXEC)

obj/%.o : src/%.cpp
	$(CXX) -o $@ -c $< $(SFML_INCLUDE)

$(EXEC) : $(OBJ)
	$(CXX) -o $@ $^ $(SFML_LIBS) $(SFML_LIB)