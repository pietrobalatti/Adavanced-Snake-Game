#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game();
  void Init(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void InitializeData();
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void End();
  int GetScore() const;
  int GetSize() const;
  int GetRecord() const;
  std::string GetRecordPlayer() const;
  Controller::Selection selection = Controller::Selection::Easy;

 private:
  Snake snake;
  SDL_Point food;
  bool welcome_window{true};
  bool window_destruction{false};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int grid_width;
  int grid_height;
  int score{0};
  int record_score{0};
  std::string record_player{"No one!"};
  Controller::Selection game_mode = Controller::Selection::Easy;
  std::vector<std::string> record_files{"record_easy.txt","record_std.txt","record_hard.txt"};
  
  void RetrieveRecordData();
  void StoreRecordData(std::string &player_name);
  void PlaceFood();
  void Update();
  void setMode(Renderer &renderer, Controller::Selection &game_mode);
};

#endif