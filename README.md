# Skyward Bound 
The OOP Project created by Muhammad Usman Zaka, Andrew Wong, Vinh Bui

README
 
 
Welcome to Skyward Bound, a tile based adventure platformer game developed as a major project for COMP SCI 1102.
This README file includes instructions on how to compile, run, and play the associated game.
 
Skyward Bound is desgined to be an immersive platformer experience with user-friendly elements. Players will navigate through a GUI and levels which pose different challenges, enemies and power-ups.
 
 
**Table of Contents**
* Requirements
* Installation
* Running the Game
* Controls
* Gameplay Tips
* Navigation
* Credits
 
 
**Requirements**
Before beginning, ensure you have the following installed:
* Git: version control intended to clone the repo
* SFML: graphics and audio library
* C++ Compiler: preferrable one that supports C++11 (e.g. GCC, Clang)
 
**Installation**
1. Clone the Repository:
git clone [https://github.com/usman-zaka/skyward-bound]
 
2. Compile the Game: See instructions below

[MACOS] (Compile using Makefile)

[WINDOWS/LINUX USERS] (Use the command below)
g++ -o game  main.cpp gameEngine.cpp Button.cpp Level.cpp Character.cpp Block.cpp Player.cpp Item.cpp powerUp.cpp Enemy.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

 
**Running the Game**
After the installation is complete, you can run the game in the terminal using the following command:
./game
 
**Controls**
* W,D: Move left and move right
* Spacebar: Jump
* Mouse: Navigate menus
 
 
**Gameplay Tips**
* Avoid Enemies: Jump on enemies to kill them or avoid them to avoid losing lives.
* Flag: Each level is completed by reaching the flag. Complete the level as fast as possible
* Power-Ups: Collect fruit power-ups to gain special abilities.
* Player will drown in the water.
 
 
**Navigation**
* Initial Menu: Create a new game or load an existing game.
* Level Menu: Choose to play a level
 
 
**Credits**
* Game Development: Muhammad Usman Zaka, Andrew Wong, Vinh Bui
* Graphics: Deep AI (public domain), Brackeys' Platformer Bundle (Creative Commons Zero (CC0) license), Daniel Tołwiński, Charles-wildmore, Free Sky Backgrounds- itch.io
* Music: Brackeys' Platformer Bundle (Creative Commons Zero (CC0) license)
