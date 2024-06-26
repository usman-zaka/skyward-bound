#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>

#include "Character.h"
#include "Player.h"

class Enemy : public Character {
 //All the required data members 
 private:
  sf::RectangleShape* body;
  sf::Vector2f size;
  sf::Vector2f position;
  sf::Texture* spriteTexture;
  sf::Sprite* sprite;
  sf::IntRect* currentFrame;
  sf::Vector2f position1;
  sf::Vector2f position2;
  int target;

 public:
  Enemy(sf::Vector2f position1, sf::Vector2f position2);
  ~Enemy();
  void move(std::string a);
  void attack();
  void jump();
  void draw(sf::RenderWindow* window);
  bool checkCollisionWithPlayer(Player* player);
  void killPlayer(Player* player);
};

#endif