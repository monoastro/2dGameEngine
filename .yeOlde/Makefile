CXX		:= g++
CXX_FLAGS 	:= -Wall -Wextra -std=c++17
BIN		:= bin
SRC		:= src
INCLUDE		:= include
LIB		:= lib

LIBRARIES	:= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXECUTABLE	:= main

run: $(BIN)/$(EXECUTABLE)
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES)
