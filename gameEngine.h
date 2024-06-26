#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "Block.h"
#include "Button.h"
#include "Level.h"
// Main class that brings all components together and runs the entire thing
class gameEngine {
 // All required data members
 private:
  sf::RenderWindow* window;
  Button* newGame;
  Button* easyLevel;
  sf::Font pixelFont;
  sf::Music soundTrack;
  sf::Texture backgroundTexture;
  sf::Sprite background;
  sf::Vector2u textureSize;
  sf::Vector2u windowSize;
  float scaleX;
  float scaleY;
  Level* level;
  Player* player;
  sf::Font titleFont;
  sf::Text titleText;
  Button* quit;
  sf::Font gameOverFont;
  sf::Text gameOverText;
  sf::Texture skullTexture;
  sf::Sprite skull;
  sf::Texture trophyTexture;
  sf::Sprite trophy;
  sf::Text scoreText;

 public:
  gameEngine(int size, std::string title);
  ~gameEngine();
  void run();
};
#endif