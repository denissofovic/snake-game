CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXE = snake

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

%.o: %.cpp snake.h food.h field.h game.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: all clean
