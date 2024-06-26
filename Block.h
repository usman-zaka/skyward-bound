#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
#include <string>

class Block {
 private:
  // All neccessary data members such as the body(hitbox), sprites and their
  // textures and etc
  sf::RectangleShape* body;
  sf::Vector2f size;
  sf::Vector2f position;
  sf::Texture* spriteTexture;
  sf::Sprite* sprite;
  float scaleX;
  float scaleY;
  bool isOnBlock;

 public:
  // All necesssary function members such as the constructor and destructor and
  // other required functionality
  Block(std::string spriteFile, sf::Vector2f size);
  void draw(sf::RenderWindow* window);
  void setPosition(sf::Vector2f position);
  ~Block();
  sf::RectangleShape* getHitbox();
  sf::Sprite* getSprite();
  bool getIsOnBlock();
  void setIsOnBlock(bool status);
};
#endif