#include "game.h"
#include <iostream>
#include "SDL.h"
#include <fstream>
#include <sstream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  RetrieveRecordData();
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    if(welcome_window){
      controller.HandleInput(running, selection);
      renderer.Render(selection);
      if(selection == Controller::Selection::Enter){
        welcome_window = false;
        setMode(renderer, prev_selection);
      }
      prev_selection = selection;
    }else if (snake.alive) {
      controller.HandleInput(running, snake);
      Update();
      renderer.Render(snake, food);
    }else{
      renderer.RenderEndScreen();
      window_destruction = true;
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      std::string title;
      if(welcome_window)
        title = "Select mode";
      else{
        // Print actual score and also stored record
        title = "Snake Score: " + std::to_string(score) + "\t\tRecord: " + std::to_string(record_score) + " (" + record_player + ")";
        // Uncomment this if you want to print FPS as well
        //title+= "\t\t(FPS: " + std::to_string(fps) + ")";
      }
      renderer.UpdateWindowTitle(title);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    // If end window has been rendered, keep the screen for 2 seconds and then close the game
    if (window_destruction) {
      SDL_Delay(2000);
      break;
    }
  }
}

void Game::End(){
  // End of the game
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << GetScore() << "\n";
  std::cout << "Size: " << GetSize() << "\n";
  if(GetScore() > record_score) {
    std::cout << "\nCongratulations, you set a new record! Previous record was " << record_score << "\n";
    std::cout << "Enter your name: ";
    std::string player_name;
    std::cin >> player_name;
    StoreRecordData(player_name);
    std::cout << "Your name has been stored. Bye bye!" << "\n";
  } 
}

void Game::RetrieveRecordData(){
  // Read record data from file
  std::ifstream record_file;
  record_file.open("../data/record.txt");
  if (record_file) {
    std::cout << "Reading data from \"record\" file..." << "\n";
    std::string line;
    getline(record_file, line);
    std::istringstream linestream(line);
    linestream >> record_score >> record_player;
    std::cout << "Record: " << record_score << " (" << record_player<< ")"<< "\n";
  } 
}

void Game::StoreRecordData(std::string &player_name){
  std::ofstream record_file;
  record_file.open("../data/record.txt");
  if (record_file) {
    record_file << GetScore() << " " << player_name;
    record_file.close();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

void Game::setMode(Renderer &renderer, Controller::Selection &prev_selection) {
  std::size_t width;
  std::size_t height;
  switch (prev_selection)
  {
  case Controller::Selection::Easy:
    width = 800;
    height = 800;
    break;

  case Controller::Selection::Std:
    width = 640;
    height = 640;
    break;

  case Controller::Selection::Hard:
    width = 400;
    height = 400;
    break;
  
  default:
    break;
  }
  renderer.setScreenSize(width, height);
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetRecord() const { return record_score; }
std::string Game::GetRecordPlayer() const { return record_player; }