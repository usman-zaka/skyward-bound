#include "Player.h"

#include <iostream>
// The constructor for a Player object
// Creates the player and it's sprite and hitbox
// Sets the player's walking speed, health, jump speed etc,
Player::Player(std::string username) {
  //Intialising player attributes
  this->username = username;
  this->health = 1;
  this->speed = 2.5;
  this->size = sf::Vector2f(35, 55);

  //Hitbox for player
  body = new sf::RectangleShape(size);

  //Loading in sprite texutre
  spriteTexture = new sf::Texture();
  if (!(*spriteTexture).loadFromFile("knight.png")) {
    std::cout << "Error loading file" << std::endl;
  }

  //Loading in sound effects
  if (!jumpBuffer.loadFromFile("jump.wav")) {
    std::cout << "Error loading file" << std::endl;
  }

  if (!powerupBuffer.loadFromFile("power_up.wav")) {
    std::cout << "Error loading file" << std::endl;
  }

  //Setting the sound buffers for the sound effects
  jumpSFX.setBuffer(jumpBuffer);
  powerupSFX.setBuffer(powerupBuffer);

  //As with enemy since we are using a sprite sheet instead 
  //of an individual sprite, we need to 'crop'
  sprite = new sf::Sprite();
  currentFrame = new sf::IntRect(0, 0, 32, 32);
  sprite->setTexture(*spriteTexture);
  sprite->setScale(3, 3);
  body->setPosition(sf::Vector2f(30, 615));
  sprite->setPosition(sf::Vector2f(0, 585));
  sprite->setTextureRect(*currentFrame);

  //intially player is not jumping or falling
  isJumping = false;
  isFalling = false;
  gravity = 0.01;  // 0.01 is a number we tinkered with and works best for us
  jumpStrength = 1.7;  // 1.7 is a number we tinkered with and works best for us


  isInvulnerable = false;
  invulnerabilityDuration = sf::seconds(10);
};

Player::~Player() {
  delete spriteTexture;
  delete sprite;
  delete body;
  delete currentFrame;
};

void Player::move(std::string direction) {
  if (direction.compare("right")) {
    body->move(-speed, 0);
    sprite->move(-speed, 0);
  } else if (direction.compare("left")) {
    body->move(speed, 0);
    sprite->move(speed, 0);
  }
};

void Player::jump() {
  if (!isJumping && !isFalling) {
    isJumping = true;
    velocityY = -jumpStrength;
    jumpSFX.play();
  }
};

void Player::attack() {

};
void Player::draw(sf::RenderWindow* window) {
  window->draw(*sprite);
  //window->draw(*body);
}

void Player::update() {
  if (isInvulnerable) {
    if (invulnerabilityTimer.getElapsedTime() >= invulnerabilityDuration) {
      isInvulnerable = false;
    }
  }

  if (isJumping) {
    body->move(0, velocityY);
    sprite->move(0, velocityY);
    velocityY += gravity;

    if (velocityY >= 0) {
      isJumping = false;
      isFalling = true;
    }
  }
  if (isFalling) {
    body->move(0, velocityY);
    sprite->move(0, velocityY);
    velocityY += gravity;

    if (sprite->getPosition().y >= 585) {
      body->setPosition(body->getPosition().x, 585);
      sprite->setPosition(sprite->getPosition().x, 585);
      isFalling = false;
    }
  }
}

sf::RectangleShape* Player::getHitbox() { return this->body; }

void Player::setHealth(int health) { this->health = health; }

sf::Sprite* Player::getSprite() { return this->sprite; }

void Player::use(char powerup) {
  switch (powerup) {
    case 'a':
      this->health = 2;
      std::cout << "apple used!" << std::endl;
      powerupSFX.play();
      break;
    case 'p':
      this->speed = 3.5;
      std::cout << "pear used!" << std::endl;
      powerupSFX.play();
      break;
    case 'g':
      this->jumpStrength = 2.5;
      std::cout << "grape used!" << std::endl;
      powerupSFX.play();
      break;
  }
}

//Getters and Setters
int Player::getHealth() { return this->health; }

bool Player::getVulnerability() { return this->isInvulnerable; }

void Player::setVulnerability(bool vulnerability) {
  this->isInvulnerable = vulnerability;
}

sf::Clock Player::getVulnerabilityTimer() { return this->invulnerabilityTimer; }

bool Player::getIsJumping() { return this->isJumping; }

bool Player::getIsFalling() { return this->isFalling; }

float Player::getGravity() { return this->gravity; }

float Player::getVelocityY() { return this->velocityY; }

void Player::setJumping(bool jumping) { this->isJumping = jumping; }

void Player::setFalling(bool falling) { this->isFalling = falling; }

void Player::setVelocityY(float velocity) { this->velocityY = velocity; }

sf::Time Player::getInvulnerabilityDuration() {
  return this->invulnerabilityDuration;
}

sf::Vector2f Player::getPosition() { return sprite->getPosition(); };