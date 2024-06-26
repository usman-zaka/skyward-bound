#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Item.h"
#include "Player.h"

//The way we differentiate between the different powerups
enum PowerUpType { DOUBLE_HEALTH, DOUBLE_SPEED, DOUBLE_JUMP };

class powerUp : public Item {
 //Relevant data members
 private:
  char type;
  int column_index;
  int row_index;

 public:
  //Relevant Function Members
  sf::IntRect* currentFrame;
  powerUp(std::string name, PowerUpType type);
  void draw(sf::RenderWindow* window);
  void setPosition(sf::Vector2f position);
  ~powerUp();
  char getType();
  bool checkCollisionWithPlayer(Player* player);
};

#endif