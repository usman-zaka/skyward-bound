#include "Button.h"
// Constructor that constructs a button with the given parameters as well as the
// text for it
Button::Button(std::string txt, sf::Vector2f size, sf::Color backgroundColour,
               sf::Font* font, sf::Color txtColour, int charSize) {
  // Creating the body of the button
  button = new sf::RectangleShape(size);
  button->setFillColor(backgroundColour);
  button->setPosition(625, 300);

  // By default buttons are not clickable
  this->allowClicking = false;

  // Creating the text and centering it on the button
  // Modfiying certain properties of the text like outline and color
  text = new sf::Text(txt, *font, charSize);
  sf::FloatRect textRect = text->getLocalBounds();
  text->setOrigin(textRect.width / 2, textRect.height / 2);
  text->setPosition(button->getPosition().x + size.x / 2,
                    button->getPosition().y + size.y / 2);
  text->setFillColor(txtColour);
  text->setOutlineColor(sf::Color::Black);
  text->setOutlineThickness(0.5);

  // By default, a button is in the state of not being clicked;
  this->clicked = false;
}

// This set position function does it so that no matter where we move the
// button, the text Always remains centered on the button
void Button::setPosition(sf::Vector2f position) {
  button->setPosition(position);
  sf::FloatRect textRect = text->getLocalBounds();
  text->setOrigin(textRect.width / 2, textRect.height / 2);
  text->setPosition(position.x + button->getSize().x / 2,
                    position.y + button->getSize().y / 2);
}

void Button::draw(sf::RenderWindow* window) {
  window->draw(*button);
  window->draw(*text);
}

// Checks if a button has been clicked by checking if the mouse position is
// within the Global bounds of the button
bool Button::isClicked(sf::Vector2f mousePosition) {
  clicked = button->getGlobalBounds().contains(mousePosition);
  if (clicked == true && allowClicking == true) {
    std::cout << "button clicked!" << std::endl;
  }
  return clicked;
}

// Getters and Setters
void Button::setClickability(bool permission) {
  this->allowClicking = permission;
}

bool Button::getClickability() { return this->allowClicking; }
