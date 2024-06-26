#include "Enemy.h"

#include <iostream>

Enemy::Enemy(sf::Vector2f position1, sf::Vector2f position2) {
  // Intialises basic stats for an enemy and the body with the relevant size
  this->health = 1;
  this->speed = 1;
  this->size = sf::Vector2f(36, 24);

  body = new sf::RectangleShape(size);

  // Loading in the sprite texture for the enemy
  spriteTexture = new sf::Texture();
  if (!(*spriteTexture).loadFromFile("slime_green.png")) {
    std::cout << "Error loading file" << std::endl;
  }

  // Since we are using a full sprite sheet instead of an individual sprite,
  // We need to 'crop' the sprite sheet and get the relevant sprite
  // This is done by creating an IntRect of the relevant size
  // The sprite is also scaled up so it is big enough
  sprite = new sf::Sprite();
  currentFrame = new sf::IntRect(0, 0, 24, 24);
  sprite->setTexture(*spriteTexture);
  sprite->setScale(3, 3);
  body->setPosition(sf::Vector2f(position1.x + 18, 650));
  sprite->setPosition(sf::Vector2f(position1.x, 600));
  sprite->setTextureRect(*currentFrame);

  target = 2;
  // The two positions the enemy will patrol between
  this->position1 = position1;
  this->position2 = position2;
};

Enemy::~Enemy() {
  delete spriteTexture;
  delete sprite;
  delete body;
};

// The patrolling function
void Enemy::move(std::string a) {
  // Get current position
  sf::Vector2f currentPosition = sprite->getPosition();

  if (this->target == 2) {
    if (currentPosition.x < position2.x) {
      sprite->move(speed, 0);
      body->move(speed, 0);
    }
    if (currentPosition.x >= position2.x) {
      this->target = 1;
    }
  } else if (target == 1) {
    if (currentPosition.x > position1.x) {
      sprite->move(-speed, 0);
      body->move(-speed, 0);
    }
    if (currentPosition.x <= position1.x) {
      this->target = 2;
    }
  }
}

void Enemy::attack() {

};

void Enemy::draw(sf::RenderWindow* window) {
  window->draw(*sprite);
  // window->draw(*body);
}

void Enemy::jump() {

};

bool Enemy::checkCollisionWithPlayer(Player* player) {
  if (body->getGlobalBounds().intersects(
          player->getHitbox()->getGlobalBounds())) {
    return true;
  }

  return false;
}

void Enemy::killPlayer(Player* player) {
  player->getSprite()->setPosition(sf::Vector2f(0, 585));
  player->getHitbox()->setPosition(sf::Vector2f(30, 615));
}