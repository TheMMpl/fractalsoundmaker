CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall

OBJ = main.o engine.o fractals.o wavfile.o soundmaker.o settings.o gui.o
SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

INC_DIR=.
SRC_DIR=./source

PCH_SRC = source/pch.hpp
#PCH_HEADERS = 
PCH_OUT = source/pch.hpp.gch

NAME = fsm

all: $(OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(SFML)
%.o: $(SRC_DIR)/%.cpp
	@$(CXX) $(CXXFLAGS) -c -I$(INC_DIR) $< -o $@
clean:
	@rm -f $(NAME) $(OBJ)



