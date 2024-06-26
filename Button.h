#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>

// Blueprint for all buttons used in the game
class Button {
  // Data members include the shape of the button, the text inside the button
  // and the state of the button (clicked/not clicked)
 private:
  sf::RectangleShape* button;
  sf::Text* text;
  bool clicked;
  bool allowClicking;

 public:
  // Behaviour includes being able to modify the dimensions of the button,
  // drawing the button and checking it's state
  Button(std::string txt, sf::Vector2f size, sf::Color backgroundColour,
         sf::Font* font, sf::Color txtColor, int charSize);
  void setPosition(sf::Vector2f position);
  void draw(sf::RenderWindow* window);
  bool isClicked(sf::Vector2f mousePosition);
  void setClickability(bool permission);
  bool getClickability();
};
#endif