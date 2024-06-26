#include "Block.h"

#include <iostream>

Block::Block(std::string spriteFile, sf::Vector2f size) {
  // Creating the hitbox for the block
  this->size = size;
  body = new sf::RectangleShape(size);

  // Loading in the sprite texture for the sprite we are using for the block
  spriteTexture = new sf::Texture();
  if (!(*spriteTexture).loadFromFile(spriteFile)) {
    std::cout << "Error loading file" << std::endl;
  }

  // Scaling the sprite of the block based on the size of the body so that the
  // sprite neatly overlays the body
  scaleX = (float)size.x / spriteTexture->getSize().x;
  scaleY = (float)size.y / spriteTexture->getSize().y;

  // Setting the texture of the sprite to the texture we loaded in
  sprite = new sf::Sprite();
  sprite->setTexture(*spriteTexture);
  sprite->setScale(scaleX, scaleY);

  // Logging message to check if a block has been created properly
  std::cout << "Block created successfully!" << std::endl;
  this->position = sf::Vector2f(45, 45);

  // Setting the position of the block to what is required by the parameter
  body->setPosition(position);
  sprite->setPosition(position);

  // Toggling a property of the block
  this->isOnBlock = false;
}

void Block::setPosition(sf::Vector2f position) {
  body->setPosition(position);
  sprite->setPosition(position);
}

void Block::draw(sf::RenderWindow* window) {
  window->draw(*sprite);
  // window->draw(*body);
}

// Destructor
Block::~Block() {
  delete body;
  delete spriteTexture;
  delete sprite;
}

// Getters and Setters
sf::RectangleShape* Block::getHitbox() { return this->body; }

sf::Sprite* Block::getSprite() { return this->sprite; }

void Block::setIsOnBlock(bool status) { this->isOnBlock = status; }

bool Block::getIsOnBlock() { return this->isOnBlock; }