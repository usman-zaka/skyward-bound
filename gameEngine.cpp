#include "gameEngine.h"

// Constructor implementation
// Constructor creates and renders a new window
// Our font is also loaded in from a file
// The buttons for the main menu are also created in the constructor
gameEngine::gameEngine(int size, std::string title) {
  //Creating a window of the relevant size
  window = new sf::RenderWindow(sf::VideoMode(size, size / 2), title,
                                sf::Style::Close | sf::Style::Titlebar);

  // Loading in the fonts
  if (!pixelFont.loadFromFile("PixelOperator8-Bold.ttf")) {
    std::cout << "Error loading file" << std::endl;
  }

  if (!titleFont.loadFromFile("TheSerifHandXtraBlk.ttf")) {
    std::cout << "Error loading file" << std::endl;
  }

  if (!gameOverFont.loadFromFile("gameoverfont.ttf")) {
    std::cout << "Error loading file" << std::endl;
  }

  //Loading in the sprite textures for the skull and trophy for the game over and victory screen
  if (!skullTexture.loadFromFile("skull.png")) {
    std::cout << "Error loading file" << std::endl;
  }

  skull.setTexture(skullTexture);

  if (!trophyTexture.loadFromFile("trophy.png")) {
    std::cout << "Error loading file" << std::endl;
  }

  trophy.setTexture(trophyTexture);

  // Pointer that points to our font
  sf::Font* ptr = &pixelFont;

  // Loading in the music
  if (!soundTrack.openFromFile("time_for_adventure.ogg")) {
    std::cout << "Error loading file" << std::endl;
  }
  // Playing and looping the music
  soundTrack.play();
  soundTrack.setLoop(true);

  // Loading the background image in
  if (!backgroundTexture.loadFromFile("SkywardBound.jpg")) {
    std::cout << "Error loading file" << std::endl;
  }

  // Scaling the background image
  textureSize = backgroundTexture.getSize();
  windowSize = window->getSize();
  scaleX = (float)windowSize.x / textureSize.x;
  scaleY = (float)windowSize.y / textureSize.y;
  background.setTexture(backgroundTexture);
  background.setScale(scaleX, scaleY);

  // Creating all relevant buttons
  newGame = new Button("New Game", sf::Vector2f(250, 50), sf::Color::Yellow,
                       ptr, sf::Color::White, 20);
  newGame->setPosition(sf::Vector2f(625, 350));

  easyLevel = new Button("Easy", sf::Vector2f(250, 50), sf::Color::Yellow, ptr,
                         sf::Color::White, 20);
  easyLevel->setPosition(sf::Vector2f(625, 350));

  quit = new Button("Quit", sf::Vector2f(250, 50), sf::Color::Black,
                    &gameOverFont, sf::Color::White, 20);

  //Creating a level and player 
  level = new Level(1500, "Easy Level");
  player = level->getPlayer();

  // Initialize and set the title text properties
  titleText.setFont(titleFont);
  titleText.setString("Skyward Bound");
  titleText.setCharacterSize(150);
  titleText.setFillColor(sf::Color::White);
  titleText.setPosition(sf::Vector2f(435, 50));
}

// Main Run method that runs everything
void gameEngine::run() {
  //Making the new game button clickable so the user can actually click it
  newGame->setClickability(true);
  bool inMainMenu = true;  // Intially we are in the main menu
  bool inLevelMenu = false;
  bool inEasyLevel = false;

  while (window->isOpen())  // Main While Loop on which the entire game runs
  {
    sf::Event e;
    while (window->pollEvent(e)) {
      // Checks if the user has clicked the "x" button to close the window
      if (e.type == sf::Event::Closed) {
        window->close();
      }
      // If the user tries to resize, it won't let them it'll just snap back
      if (e.type == sf::Event::Resized) {
        // Reset the window size to the original size
        window->setSize(sf::Vector2u(1500, 750));
      }

      //It checks if keypressed event actually has happened and that the space key has been clicked
      //If it has, it calls the jump function for the player
      if (e.type == sf::Event::KeyPressed &&
          e.key.code == sf::Keyboard::Space) {
        player->jump();
      }
      // Checks if the user has clicked "New Game"
      // We need to ensure that the event is actually a mouse click and that is
      // click from the left mouse button
      if (e.type == sf::Event::MouseButtonPressed &&
          e.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePosition =
            window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        if (newGame->isClicked(mousePosition) == true) {
          // First if statement checks if the button has been clicked
          // Second if statement checks if the button has clicking permissions
          // If it does, the we change to levelMenu and make new game button not clickable anymore
          if (newGame->getClickability() == true) {
            inMainMenu = false;
            inLevelMenu = true;
            newGame->setClickability(false);
            easyLevel->setClickability(true);
          }

          else if (easyLevel->isClicked(mousePosition) == true) {
            if (easyLevel->getClickability() == true) {
              inMainMenu = false;
              inLevelMenu = false;
              inEasyLevel = true;
              easyLevel->setClickability(false);
              quit->setClickability(true);
              level->restartTimer();
            }
          }
        }
      }
      //Checking for movement input (A and D keys)
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->move("left");
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->move("right");
      }
    }
    // Clears the window by default
    window->clear(sf::Color::Cyan);

    // If we are in the main menu it will create the relevant buttons
    if (inMainMenu == true) {
      window->draw(background);
      window->draw(titleText);
      newGame->draw(window);

    }
    // If we are in the Level Menu it will create the relevant buttons
    else if (inLevelMenu == true) {
      newGame->setClickability(false);
      window->draw(background);
      easyLevel->draw(window);

    }

    //Main logic for running the entire level
    //If the player is not dead and the game hasn't finished
    //Then the level will be rendered
    //If they die, the logic for the gameover screen is executed
    //If they win, the logic for the victory screen is executed
    else if (inEasyLevel == true) {
      if (!level->getisDead() && !level->getisFinished()) {
        level->renderLevel(window);
      }

      else if (level->getisDead() == true) {
        window->clear(sf::Color::Black);
        soundTrack.stop();
        window->setView(window->getDefaultView());

        gameOverText.setFont(gameOverFont);
        gameOverText.setString("GAME OVER");
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setCharacterSize(50);
        gameOverText.setPosition(sf::Vector2f(510, 100));
        window->draw(gameOverText);

        skull.setScale(0.5, 0.5);
        skull.setPosition(620, 200);
        window->draw(skull);

        quit->setPosition(sf::Vector2f(625, 550));
        quit->draw(window);
        sf::Vector2f mousePosition =
            window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (e.type == sf::Event::MouseButtonPressed &&
            e.mouseButton.button == sf::Mouse::Left) {
          if (quit->isClicked(mousePosition) == true) {
            if (quit->getClickability() == true) {
              window->close();
            }
          }
        }
      }

      else if (level->getisFinished() == true) {
        window->clear(sf::Color::Black);
        soundTrack.stop();
        window->setView(window->getDefaultView());

        std::string score = level->playerTime();
        scoreText.setFont(gameOverFont);
        scoreText.setString(score);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setCharacterSize(40);
        scoreText.setPosition(sf::Vector2f(580, 560));
        window->draw(scoreText);

        gameOverText.setFont(gameOverFont);
        gameOverText.setString("VICTORY");
        gameOverText.setFillColor(sf::Color::Green);
        gameOverText.setCharacterSize(50);
        gameOverText.setPosition(sf::Vector2f(550, 100));
        window->draw(gameOverText);

        trophy.setScale(2, 2);
        trophy.setPosition(620, 200);
        window->draw(trophy);

        quit->setPosition(sf::Vector2f(640, 650));
        quit->draw(window);
        sf::Vector2f mousePosition =
            window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (e.type == sf::Event::MouseButtonPressed &&
            e.mouseButton.button == sf::Mouse::Left) {
          if (quit->isClicked(mousePosition) == true) {
            if (quit->getClickability() == true) {
              window->close();
            }
          }
        }
      }
    }

    // Displaying everything on the window
    window->display();
  }
}

// Destructor ensures there are no memory leaks
gameEngine::~gameEngine() {
  delete window;
  delete newGame;
  delete easyLevel;
  delete level;
  delete player;
  delete quit;
}
