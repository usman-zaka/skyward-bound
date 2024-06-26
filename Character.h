#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics.hpp>
#include <string>

class Character {
  // Key attributes that every 'character' has
  // Protected access modifier so that when we inherit, the attributes will be
  // private not hidden
 protected:
  std::string name;
  int health;
  float speed;
  sf::RectangleShape body;
  sf::Vector2f position;
  int height;
  int width;

 public:
  // Standard function members
  Character();
  ~Character();
  virtual void move(std::string) = 0;
  virtual void jump() = 0;
  virtual void attack() = 0;
};

#endif