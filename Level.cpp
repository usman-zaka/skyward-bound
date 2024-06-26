#include "Level.h"

#include <cmath>
#include <iostream>

Level::Level(int size, std::string title) {
  //Loading in the sound effects
  if (!damageBuffer.loadFromFile("hitHurt.wav")) {
    std::cout << "Error loading file" << std::endl;
  }

  if (!drowningBuffer.loadFromFile("drowning.wav")) {
    std::cout << "Error loading file" << std::endl;
  }
  //Creating the sound buffers for the different sound effects
  damageSFX.setBuffer(damageBuffer);
  drowningSFX.setBuffer(drowningBuffer);
  
  //Loading in some sprite textures for the background and the arrow that tells the user
  //That they are going in the wrong direction
  if (!levelBackgroundTexture.loadFromFile("clouds.png")) {
    std::cout << "Error loading file" << std::endl;
  }

  if (!arrowTexture.loadFromFile("arrow.png")) {
    std::cout << "Error loading file" << std::endl;
  }
  arrow.setTexture(arrowTexture);

  levelBackgroundTexture.setRepeated(true);

  //This is the beginning of intialising all the blocks and every entity so they can 
  //Be rendered later
  numBlocks = 93;
  numStones = 30;
  numWater = 38;
  numTrees = 30;
  numPlatforms = 12;
  
  //The different blocks
  grass = new Block*[numBlocks];
  dirt = new Block*[numBlocks];
  stones = new Block*[numStones];
  water = new Block*[numWater];
  trees = new Block*[numTrees];
  platforms = new Block*[numPlatforms];

  //This is the winning condition
  flag = new Block("flag.png", sf::Vector2f(40, 40));

  //Various for loops to intialise everything
  for (int i = 0; i < numBlocks; i++) {
    grass[i] = new Block("grass.png", sf::Vector2f(40, 40));
    dirt[i] = new Block("dirt.png", sf::Vector2f(40, 40));
  }
  for (int i = 0; i < numStones; i++) {
    stones[i] = new Block("stone.png", sf::Vector2f(40, 40));
  }

  for (int i = 0; i < numWater; i++) {
    water[i] = new Block("water.png", sf::Vector2f(40, 88));
  }

  for (int i = 0; i < numTrees; i++) {
    trees[i] = new Block("tree.png", sf::Vector2f(20, 40));
  }

  for (int i = 0; i < numPlatforms; i++) {
    platforms[i] = new Block("green_platform.png", sf::Vector2f(50, 20));
  }
  //Logging message to let us know that the things are working
  std::cout << "Level created successfully!" << std::endl;

  //Intialising all entities 
  player = new Player("jack");
  enemy = new Enemy(sf::Vector2f(455, 585), sf::Vector2f(810, 585));
  enemy2 = new Enemy(sf::Vector2f(1080, 585), sf::Vector2f(1280, 585));
  enemy3 = new Enemy(sf::Vector2f(1400, 585), sf::Vector2f(1600, 585));
  enemy4 = new Enemy(sf::Vector2f(2600, 585), sf::Vector2f(2800, 585));

  //Intialising the powerups
  numApples = 1;
  numGrapes = 1;
  numPears = 1;
  apples = new powerUp*[numApples];
  pears = new powerUp*[numPears];
  grapes = new powerUp*[numGrapes];

  apples[0] = new powerUp("Double Health", DOUBLE_HEALTH);
  pears[0] = new powerUp("Double Speed", DOUBLE_SPEED);
  grapes[0] = new powerUp("Double Jump", DOUBLE_JUMP);

  
  // Loading in the fonts
  if (!pixelFont2.loadFromFile("font.ttf")) {
    std::cout << "Error loading file" << std::endl;
  }
  if (!directionFont.loadFromFile("PixelOperator8.ttf")) {
    std::cout << "Error loading file" << std::endl;
  }
  

  // This starts the timer 
  gameClock.restart();

  // By default, the player isn't dead and the game isn't finished yet
  isDead = false;

  isFinished = false;
}

void Level::renderLevel(sf::RenderWindow* window) {
  // We need to save the current view so that after the background is drawn, we
  // can revert to this view
  sf::View originalView = window->getView();

  // We now change to the default view so that the background can be drawn
  window->setView(window->getDefaultView());

  // Scaling the background based on the size of the window
  levelTextureSize = levelBackgroundTexture.getSize();
  levelScaleX = (float)window->getSize().x / levelTextureSize.x;
  levelScaleY = (float)window->getSize().y / levelTextureSize.y;
  levelBackground.setTexture(levelBackgroundTexture);
  levelBackground.setScale(levelScaleX, levelScaleY);
  window->draw(levelBackground);

  // Reverting to the original view
  // We need to do this so the background remains fixed otherwise eventually
  // when the player moves far away enough The background will end
  window->setView(originalView);

  // We constantly need to update and render the text for the timer
  sf::Time elapsedTime = gameClock.getElapsedTime();
  int hours = (elapsedTime.asSeconds()) / 3600;
  int minutes = ((int)(elapsedTime.asSeconds()) % 3600) / 60;
  int seconds = (int)(elapsedTime.asSeconds()) % 60;
  int milliseconds = elapsedTime.asMilliseconds() % 1000;

  // Extract the last two digits of milliseconds
  int lastTwoDigits = milliseconds % 100;

  // Convert milliseconds to string with two decimal places
  std::string millisecondsString = std::to_string(lastTwoDigits);
  millisecondsString =
      std::string(2 - millisecondsString.length(), '0') + millisecondsString;

  // We need the time in the format HH:MM:SS:MS
  // We are concentanting each component of the Clock into our formattedTime
  // string The ? is a ternary operator and is a short hand for if then else
  // logic For example for the first one, if hours < 10 then we concatenate a 0
  // otherwise we concatenate ""
  std::string formattedTime = "";
  formattedTime += (hours < 10 ? "0" : "") + std::to_string(hours) + ":";
  formattedTime += (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":";
  formattedTime += (seconds < 10 ? "0" : "") + std::to_string(seconds) + ":";
  formattedTime += millisecondsString;

  // Formatting the text for the timer
  timerText.setFont(pixelFont2);
  timerText.setCharacterSize(80);
  timerText.setFillColor(sf::Color::Red);
  timerText.setPosition(1325, -45);
  timerText.setString(formattedTime);

  // Formatting the text for the directions that tell the player waht controls
  // to use
  directionText.setFont(directionFont);
  directionText.setCharacterSize(15);
  directionText.setFillColor(sf::Color::White);
  directionText.setPosition(50, 500);
  directionText.setString(
      "To move LEFT:'A'\nTo move RIGHT: 'D'\nTo JUMP: 'Spacebar'");

  // Variables that are used to set the position for the dirt and grass blocks
  int grassX = 0;
  int grassY = window->getSize().y - 80;
  int dirtX = 0;
  int dirtY = window->getSize().y - 40;

  // draws grass and dirt
  for (int i = 0; i < numBlocks; i++) {
    grass[i]->setPosition(sf::Vector2f(grassX, grassY));
    grass[i]->draw(window);
    grassX = grassX + 40;
    dirt[i]->setPosition(sf::Vector2f(dirtX, dirtY));
    dirt[i]->draw(window);
    dirtX = dirtX + 40;
  }

  //Set of for loops to draw the stone blocks
  for (int i = 0; i < 2; i++) {
    stones[i]->setPosition(sf::Vector2f(440, grassY - 40 * (i + 1)));
    stones[i]->draw(window);
  }

  for (int i = 2; i < 5; i++) {
    stones[i]->setPosition(sf::Vector2f(880, grassY - 40 * (i - 1)));
    stones[i]->draw(window);
  }

  for (int i = 5; i < 10; i++) {
    stones[i]->setPosition(sf::Vector2f(980 + 40 * (i - 4), grassY - 240));
    stones[i]->draw(window);
  }

  for (int i = 10; i < 14; i++) {
    stones[i]->setPosition(sf::Vector2f(1800, grassY - 40 * (i - 9)));
    stones[i]->draw(window);
  }

  for (int i = 14; i < 17; i++) {
    stones[i]->setPosition(
        sf::Vector2f(2140 + 40 * (i - 13), grassY - 40 * (3)));
    stones[i]->draw(window);
  }

  for (int i = 17; i < 25; i++) {
    stones[i]->setPosition(
        sf::Vector2f(2300 + 40 * (i - 16), grassY - 40 * (7)));
    stones[i]->draw(window);
  }

  for (int i = 25; i < 30; i++) {
    stones[i]->setPosition(
        sf::Vector2f(2900 + 40 * (i - 24), grassY - 40 * (7)));
    stones[i]->draw(window);
  }

  // Drawing water
  for (int i = 0; i < 5; i++) {
    water[i]->setPosition(sf::Vector2f(880 + 40 * (i + 1), grassY - 8));
    water[i]->draw(window);
  }

  for (int i = 5; i < 8; i++) {
    water[i]->setPosition(sf::Vector2f(1800 + 40 * (i - 4), grassY - 8));
    water[i]->draw(window);
  }
  //Drawing the tree stems at the end of the level
  for (int i = 0; i < 3; i++) {
    trees[i]->setPosition(sf::Vector2f(3727, grassY - 40 * (i + 1)));
    trees[i]->draw(window);
  }

  for (int i = 3; i < 9; i++) {
    trees[i]->setPosition(sf::Vector2f(3927, grassY - 40 * (i - 2)));
    trees[i]->draw(window);
  }

  for (int i = 9; i < 18; i++) {
    trees[i]->setPosition(sf::Vector2f(4127, grassY - 40 * (i - 9)));
    trees[i]->draw(window);
  }

  for (int i = 18; i < 30; i++) {
    trees[i]->setPosition(sf::Vector2f(4327, grassY - 40 * (i - 20)));
    trees[i]->draw(window);
  }

  //Drawing the final water section
  for (int i = 8; i < 38; i++) {
    water[i]->setPosition(sf::Vector2f(3680 + 40 * (i - 7), grassY - 8));
    water[i]->draw(window);
  }

  //Drawing the green platforms at the end
  for (int i = 0; i < 3; i++) {
    platforms[i]->setPosition(sf::Vector2f(3615 + 50 * (i + 1), grassY - 145));
    platforms[i]->draw(window);
  }

  for (int i = 3; i < 6; i++) {
    platforms[i]->setPosition(sf::Vector2f(3815 + 50 * (i - 2), grassY - 265));
    platforms[i]->draw(window);
  }

  for (int i = 6; i < 9; i++) {
    platforms[i]->setPosition(sf::Vector2f(4014 + 50 * (i - 5), grassY - 347));
    platforms[i]->draw(window);
  }

  for (int i = 9; i < 12; i++) {
    platforms[i]->setPosition(sf::Vector2f(4214 + 50 * (i - 8), grassY - 380));
    platforms[i]->draw(window);
  }
  //Drawing the flag
  flag->setPosition(sf::Vector2f(4320, grassY - 415));
  flag->draw(window);

  //Formatting the arrow
  arrow.setScale(0.25, 0.25);
  arrow.setPosition(750, 50);

  //If the following powerups have not already been collected, their positions will be set
  if (apples[0] != nullptr) {
    apples[0]->setPosition(sf::Vector2f(236, grassY - 45));
  }

  if (grapes[0] != nullptr) {
    grapes[0]->setPosition(sf::Vector2f(980, grassY - 290));
  }

  if (pears[0] != nullptr) {
    pears[0]->setPosition(sf::Vector2f(2075, grassY - 170));
  }

  //Checking for collision with player and enemy and if there is one the player will die
  if (enemy->checkCollisionWithPlayer(player) &&
      player->getVulnerability() == false) {
    if (player->getHealth() > 0) {
      player->setHealth(player->getHealth() - 1);
      std::cout << "lost a 1 life" << std::endl;
      damageSFX.play();

      player->setVulnerability(true);
      player->getVulnerabilityTimer().restart();
    }

    if (player->getHealth() == 0) {
      enemy->killPlayer(player);
      damageSFX.play();
      isDead = true;
    }
  }

  if (enemy2->checkCollisionWithPlayer(player) &&
      player->getVulnerability() == false) {
    if (player->getHealth() > 0) {
      player->setHealth(player->getHealth() - 1);
      std::cout << "lost a 1 life" << std::endl;

      player->setVulnerability(true);
      player->getVulnerabilityTimer().restart();
      damageSFX.play();
    }

    if (player->getHealth() == 0) {
      enemy2->killPlayer(player);
      damageSFX.play();
      isDead = true;
    }
  }

  if (enemy3->checkCollisionWithPlayer(player) &&
      player->getVulnerability() == false) {
    if (player->getHealth() > 0) {
      player->setHealth(player->getHealth() - 1);
      std::cout << "lost a 1 life" << std::endl;

      player->setVulnerability(true);
      player->getVulnerabilityTimer().restart();
      damageSFX.play();
    }

    if (player->getHealth() == 0) {
      enemy3->killPlayer(player);
      damageSFX.play();
      isDead = true;
    }
  }

  if (enemy4->checkCollisionWithPlayer(player) &&
      player->getVulnerability() == false) {
    if (player->getHealth() > 0) {
      player->setHealth(player->getHealth() - 1);
      std::cout << "lost a 1 life" << std::endl;

      player->setVulnerability(true);
      player->getVulnerabilityTimer().restart();
      damageSFX.play();
    }

    if (player->getHealth() == 0) {
      enemy4->killPlayer(player);
      damageSFX.play();
      isDead = true;
    }
  }
  //For loops to check if powerups haven't already been collected, then
  //If the player collides with a powerup, they are able to use it
  //Once the powerup is used, it is deleted and then to a null ptr
  for (int i = 0; i < numApples; i++) {
    if (apples[i] != nullptr) {
      if (apples[i]->checkCollisionWithPlayer(player)) {
        player->use('a');
        delete apples[i];
        std::cout << "powerup deleted" << std::endl;
        apples[i] = nullptr;
      }
    }
  }

  for (int i = 0; i < numPears; i++) {
    if (pears[i] != nullptr) {
      if (pears[i]->checkCollisionWithPlayer(player)) {
        player->use('p');
        delete pears[i];
        std::cout << "powerup deleted" << std::endl;
        pears[i] = nullptr;
      }
    }
  }

  for (int i = 0; i < numGrapes; i++) {
    if (grapes[i] != nullptr) {
      if (grapes[i]->checkCollisionWithPlayer(player)) {
        player->use('g');
        delete grapes[i];
        std::cout << "powerup deleted" << std::endl;
        grapes[i] = nullptr;
      }
    }
  }
  //If the powerups have not been collected already hence not null pointers
  //Then the powerups will be drawn
  if (apples[0] != nullptr) {
    apples[0]->draw(window);
  }
  if (pears[0] != nullptr) {
    pears[0]->draw(window);
  }
  if (grapes[0] != nullptr) {
    grapes[0]->draw(window);
  }

  //Drawing all the enemies and making them patrol
  enemy->draw(window);
  enemy2->draw(window);
  enemy3->draw(window);
  enemy4->draw(window);
  enemy->move("a");
  enemy2->move("a");
  enemy3->move("a");
  enemy4->move("a");
  window->draw(directionText);

  //Camera Movement Mechanics
  //The view centers on the player 
  view =
      sf::View(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
  sf::Vector2f playerPosition = player->getPosition();

  //Intially we don't want it to centre, so it only centres after x > 750
  if (player->getPosition().x > 750) {
    view.setCenter(playerPosition.x, window->getView().getCenter().y);
    window->setView(view);
  }
  // Doesn't allow the player to go out of bounds 
  if (player->getPosition().x <= -20) {
    player->getSprite()->setPosition(sf::Vector2f(-20, 585));
    player->getHitbox()->setPosition(sf::Vector2f(10, 615));
  }

  // It's the same principle as the background, to keep the timer fixed on the
  // top right corner We first need to change the view to default rather than
  // the view that centers on the player Then we draw the timer and then revert
  // to the view that centers on the player
  window->setView(window->getDefaultView());
  window->draw(timerText);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    window->draw(arrow);
  }

  if (player->getPosition().x > 750) {
    window->setView(view);
  }

  //We want it to stop centring on the player when it reaches the end
  if (player->getPosition().x > 3700) {
    view = window->getDefaultView();
    view.move(2950, 0);
    window->setView(view);
  }
  //Draws the player last so it renders on top of everything
  player->draw(window);
  updatePlayer(player);
  
  //Checking win condition
  if (detectingCollisionBetweenPlayerandBlock(player, flag)) {
    isFinished = true;
    finalTime = formattedTime;
  }
}

//Destructor
Level::~Level() {
  for (int i = 0; i < numBlocks; i++) {
    delete grass[i];
    delete dirt[i];
  }
  delete[] grass;
  delete[] dirt;

  for (int i = 0; i < numApples; i++) {
    delete apples[i];
  }
  delete[] apples;

  for (int i = 0; i < numPears; i++) {
    delete pears[i];
  }
  delete[] pears;

  for (int i = 0; i < numGrapes; i++) {
    delete grapes[i];
  }
  delete[] grapes;

  delete player;
  delete enemy;
  delete enemy2;
  delete enemy3;
  delete enemy4;

  for (int i = 0; i < numStones; i++)
  {
    delete stones[i];
  }
  delete [] stones;

   for (int i = 0; i < numWater; i++)
  {
    delete water[i];
  }
  delete [] water;

   for (int i = 0; i < numTrees; i++)
  {
    delete trees[i];
  }
  delete [] trees;

   for (int i = 0; i < numPlatforms; i++)
  {
    delete platforms[i];
  }
  delete [] platforms;

  delete flag;
  
}

Player* Level::getPlayer() { return this->player; }

//Updates the player's movement when jumping and falling and after colliding with blocks
void Level::updatePlayer(Player* player) {
  if (player->getVulnerability()) {
    if (player->getVulnerabilityTimer().getElapsedTime() >=
        player->getInvulnerabilityDuration()) {
      player->setVulnerability(false);
    }
  }

  if (player->getIsJumping()) {
    for (int i = 0; i < numStones; i++) {
      stones[i]->setIsOnBlock(false);
    }

    for (int i = 0; i < numPlatforms; i++) {
      platforms[i]->setIsOnBlock(false);
    }
    //When the player jumps we gradually decrease it's velocity until it reaches 0 
    //We do this by adding gravity on to it;
    player->getHitbox()->move(0, player->getVelocityY());
    player->getSprite()->move(0, player->getVelocityY());
    player->setVelocityY(player->getVelocityY() + player->getGravity());

    //Once the velocity reaches 0, the player starts falling
    if (player->getVelocityY() >= 0) {
      player->setJumping(false);
      player->setFalling(true);
    }
    //Collision detection so if the player is under a block they can't just phase through it
    for (int i = 0; i < numStones; i++) {
      if (detectingCollisionBetweenPlayerandBlock(player, stones[i])) {
        player->getHitbox()->setPosition(
            stones[i]->getHitbox()->getPosition().x,
            player->getHitbox()->getPosition().y + 40);
        player->getSprite()->setPosition(
            stones[i]->getHitbox()->getPosition().x - 30,
            player->getSprite()->getPosition().y + 40);
        player->setJumping(false);
        player->setVelocityY(0);
        player->setFalling(true);
      }
    }
  }
  //Falling Logic
  if (player->getIsFalling()) {
    player->getHitbox()->move(0, player->getVelocityY());
    player->getSprite()->move(0, player->getVelocityY());
    player->setVelocityY(player->getVelocityY() + player->getGravity());

    //Logic for reaching the ground
    if (player->getHitbox()->getPosition().y >= 615) {
      player->getHitbox()->setPosition(player->getHitbox()->getPosition().x,
                                       615);
      player->getSprite()->setPosition(player->getSprite()->getPosition().x,
                                       585);
      player->setFalling(false);
    }
    //Collision detection so when the player falls on a block they land nicely on top of the block
    for (int i = 0; i < numStones; i++) {
      if (detectingCollisionBetweenPlayerandBlock(player, stones[i])) {
        if (!stones[i]->getIsOnBlock()) {
          std::cout << "collision with block detected!" << std::endl;
          stones[i]->setIsOnBlock(true);
          player->getHitbox()->setPosition(
              player->getHitbox()->getPosition().x,
              stones[i]->getSprite()->getPosition().y - 57);
          player->getSprite()->setPosition(
              player->getSprite()->getPosition().x,
              stones[i]->getSprite()->getPosition().y - 85);
          player->setFalling(false);
        }
      }
    }

    for (int i = 0; i < numPlatforms; i++) {
      if (detectingCollisionBetweenPlayerandBlock(player, platforms[i])) {
        if (!platforms[i]->getIsOnBlock()) {
          std::cout << "collision with block detected!" << std::endl;
          platforms[i]->setIsOnBlock(true);
          player->getHitbox()->setPosition(
              player->getHitbox()->getPosition().x,
              platforms[i]->getSprite()->getPosition().y - 57);
          player->getSprite()->setPosition(
              player->getSprite()->getPosition().x,
              platforms[i]->getSprite()->getPosition().y - 85);
          player->setFalling(false);
        }
      }
    }

  }
  //Sideways collision detection
  for (int i = 0; i < numStones; i++) {
    if (detectingCollisionBetweenPlayerandBlock(player, stones[i]) &&
        !player->getIsJumping()) {
      player->getHitbox()->setPosition(
          stones[i]->getHitbox()->getPosition().x - 30,
          player->getHitbox()->getPosition().y);
      player->getSprite()->setPosition(
          stones[i]->getHitbox()->getPosition().x - 60,
          player->getSprite()->getPosition().y);
    }
  }

  //Collision detection for water
  for (int i = 0; i < numWater; i++) {
    if (detectingCollisionBetweenPlayerandBlock(player, water[i])) {
      drowningSFX.play();
      isDead = true;
      player->getSprite()->setPosition(sf::Vector2f(0, 585));
      player->getHitbox()->setPosition(sf::Vector2f(30, 615));
    }
  }
}

//Detection a collision between the player and an individual block
bool Level::detectingCollisionBetweenPlayerandBlock(Player* player,
                                                    Block* block) {
  if (player->getHitbox()->getGlobalBounds().intersects(
          block->getHitbox()->getGlobalBounds())) {
    return true;
  }

  return false;
}

//Getters and Setters
void Level::restartTimer() { gameClock.restart(); }

bool Level::getisDead() { return this->isDead; }

bool Level::getisFinished() { return this->isFinished; }

std::string Level::playerTime() { return this->finalTime; }