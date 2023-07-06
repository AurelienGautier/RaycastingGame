CXX = g++
EXEC = bin/prog
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=obj/%.o)
SFML_LIBS = -lsfml-window -lsfml-system -lsfml-graphics

all : $(EXEC)

obj/%.o : src/%.cpp
	$(CXX) -o $@ -c $<

$(EXEC) : $(OBJ)
	$(CXX) -o $@ $^ $(SFML_LIBS)