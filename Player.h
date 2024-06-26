#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>

#include "Block.h"
#include "Character.h"

class Player : public Character {
 private:
  std::string username;
  sf::RectangleShape* body;
  sf::Vector2f size;
  sf::Vector2f position;
  sf::Texture* spriteTexture;
  sf::Sprite* sprite;
  sf::IntRect* currentFrame;
  bool isJumping;
  bool isFalling;
  float velocityY;
  float gravity;
  float jumpStrength;
  bool isInvulnerable;
  sf::Clock invulnerabilityTimer;
  sf::Time invulnerabilityDuration;
  sf::SoundBuffer jumpBuffer;
  sf::Sound jumpSFX;
  sf::SoundBuffer powerupBuffer;
  sf::Sound powerupSFX;

 public:
  Player(std::string username);
  ~Player();
  void move(std::string direction);
  void jump();
  void attack();
  void draw(sf::RenderWindow* window);
  void update();
  sf::RectangleShape* getHitbox();
  void setHealth(int health);
  sf::Sprite* getSprite();
  void use(char powerup);
  int getHealth();
  bool getVulnerability();
  void setVulnerability(bool vulnerability);
  sf::Clock getVulnerabilityTimer();
  bool getIsJumping();
  bool getIsFalling();
  float getGravity();
  float getVelocityY();
  float getJumpStrength();
  void setJumping(bool jumping);
  void setFalling(bool falling);
  void setVelocityY(float velocity);
  sf::Time getInvulnerabilityDuration();
  sf::Vector2f getPosition();
};
#endif
