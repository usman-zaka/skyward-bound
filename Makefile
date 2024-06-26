CXX = g++

# Directories for SFML libraries and headers
SFML_INCLUDE_DIR = /opt/homebrew/Cellar/sfml/2.6.1/include/
SFML_LIB_DIR = /opt/homebrew/Cellar/sfml/2.6.1/lib/

# Source Files
SOURCES = main.cpp gameEngine.cpp Button.cpp Character.cpp Player.cpp Block.cpp Level.cpp powerUp.cpp Item.cpp Enemy.cpp 

# Libraries
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Executable Name
TARGET = skywardbound

.PHONY: all clean run

all: $(TARGET) run

$(TARGET): $(SOURCES)
	$(CXX) -Wall -g -I$(SFML_INCLUDE_DIR) $(SOURCES) -o $(TARGET) -L$(SFML_LIB_DIR) $(LIBS)

run:
	./$(TARGET)  # Execute the program directly

clean:
	rm -f $(TARGET) *.o