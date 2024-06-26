#ifndef ITEM_H
#define ITEM_H
#include <SFML/Graphics.hpp>
#include <string>

class Item {
 //Required data members;
 //With protected access modifier so that when we inherit the data members become private
 protected:
  std::string name;
  sf::RectangleShape* body;
  sf::Vector2f size;
  sf::Vector2f position;
  sf::Texture* spriteTexture;
  sf::Sprite* sprite;

 public:
  virtual ~Item();
  Item();
};
#endif  // ITEM_H