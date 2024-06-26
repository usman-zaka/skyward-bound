#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "Block.h"
#include "Button.h"
#include "Enemy.h"
#include "Item.h"
#include "powerUp.h"

class Level {
 //All relevant data members
 private:
  Block** grass;
  Block** dirt;
  bool isFinished;
  int numBlocks;
  Player* player;
  Enemy* enemy;
  powerUp** apples;
  powerUp** pears;
  powerUp** grapes;
  int numApples;
  int numPears;
  int numGrapes;
  Block** stones;
  int numStones;
  sf::View view;
  Enemy* enemy2;
  Enemy* enemy3;
  Enemy* enemy4;
  Block** water;
  int numWater;
  Block** trees;
  int numTrees;
  Block** platforms;
  int numPlatforms;
  sf::Texture levelBackgroundTexture;
  sf::Sprite levelBackground;
  sf::Vector2u levelTextureSize;
  float levelScaleX;
  float levelScaleY;
  sf::Clock gameClock;
  sf::Text timerText;
  sf::Font pixelFont2;
  Block* flag;
  sf::Sound damageSFX;
  sf::SoundBuffer damageBuffer;
  sf::Sound drowningSFX;
  sf::SoundBuffer drowningBuffer;
  bool isDead;
  std::string finalTime;
  sf::Text directionText;
  sf::Font directionFont;
  sf::Texture arrowTexture;
  sf::Sprite arrow;

 //All relevant function members including constructor and destructor
 public:
  Level(int size, std::string title);
  void renderLevel(sf::RenderWindow* window);
  Player* getPlayer();
  ~Level();
  void updatePlayer(Player* player);
  bool detectingCollisionBetweenPlayerandBlock(Player* player, Block* block);
  void restartTimer();
  bool getisDead();
  bool getisFinished();
  std::string playerTime();
};
#endif