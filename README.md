# Advanced Snake Game
This game was designed to complete the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

With respect to the original game, this version:
- allows the user to select the difficulty among "easy, standard, hard", this impacts directly on the grid dimension
- renders the record score and player
- asks the user to enter his/her name once a new record is achieved
- show a "Game Over" window, when the player loses
- automatically destroys the window after the prevous above-mentioned "Game Over" windows has been shown for 2 seconds

<img src="snake_game.gif"/>

## Satisfied criteria
1. **"The project reads data from a file and process the data, or the program writes data to a file"**  
 The game stores and reads data relative to the record score and player, offering the chance to enter the player name when he/she achieves a score that is higher w.r.t. the current record.
2. **"The project uses smart pointers instead of raw pointers."**
 In main.cpp, "renderer" is instantiated as unique pointer, like this at the end of the game, a reset() is called to this object. In this way, the object deconstructor is called, the game windows terminates, and the user is able to see the terminal. Like this, the user can enter his/her name if he broke the current record.
3. **"The project accepts user input and processes the input."**
 When the game is launched, a welcome windows is shown, where the user can select various options.
4. **"The project makes use of references in function declarations."**
 Multiple functions use pass-by-reference in the project, e.g. Renderer:ReadBoardFile, Game::StoreRecordData, overloaded function Controller::HandleInput, ...
5. **"Overloaded functions allow the same function to operate on different parameters."**
 Functions Controller::HandleInput and Renderer:Render are overloaded with different signatures.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
