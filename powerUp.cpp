#include "powerUp.h"

powerUp::powerUp(std::string name, PowerUpType type) {
  //Creating hitbox for powerup
  this->size = sf::Vector2f(27, 27);
  body = new sf::RectangleShape(size);

  //Loading in sprite texture
  spriteTexture = new sf::Texture();
  if (!(*spriteTexture).loadFromFile("fruit.png")) {
    std::cout << "Error loading file" << std::endl;
  }

  sprite = new sf::Sprite();

  int cell_width = 16;
  int cell_height = 16;

  // Switch statement based on powerup type, using enumeration method from
  // powerUp.h This uses an indexing system like a matrix where the first entry
  // in the matrix is 0,0
  switch (type) {
    case DOUBLE_HEALTH:
      column_index = 0;
      row_index = 3;
      this->type = 'a';
      break;
    case DOUBLE_SPEED:
      column_index = 1;
      row_index = 2;
      break;
      this->type = 'p';
    case DOUBLE_JUMP:
      column_index = 2;
      row_index = 1;
      this->type = 'g';
      break;
  }
  //How we 'crop' the powerup sprites in the spritesheet
  int x = column_index * cell_width;
  int y = row_index * cell_height;
  currentFrame = new sf::IntRect(x, y, cell_width, cell_height);

  sprite->setTexture(*spriteTexture);
  sprite->setScale(3, 3);
  sprite->setTextureRect(*currentFrame);

  // Set positions after calculating x and y
  body->setPosition(sf::Vector2f(110 + column_index * 100, 635));
  sprite->setPosition(sf::Vector2f(100 + column_index * 100, 622));
}

void powerUp::draw(sf::RenderWindow* window) {
  window->draw(*sprite);
  // window->draw(*body);
}

powerUp::~powerUp() {
  delete body;
  delete spriteTexture;
  delete sprite;
}

char powerUp::getType() { return this->type; }

bool powerUp::checkCollisionWithPlayer(Player* player) {
  if (body->getGlobalBounds().intersects(
          player->getHitbox()->getGlobalBounds()))

  {
    return true;
  }

  return false;
}

void powerUp::setPosition(sf::Vector2f position) {
  body->setPosition(
      sf::Vector2f(position.x + 10 + column_index * 100, position.y + 13));
  sprite->setPosition(
      sf::Vector2f(position.x + column_index * 100, position.y));
}