#include <SFML/Graphics.hpp>

#include "gameEngine.h"

// main function that creates the gameEngine and calls the run method.
int main() {
  gameEngine engine(1500, "Skyward Bound");
  engine.run();
  return 0;
}