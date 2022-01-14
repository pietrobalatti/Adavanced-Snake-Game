#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void End();
  int GetScore() const;
  int GetSize() const;
  int GetRecord() const;
  std::string GetRecordPlayer() const;
  Controller::Selection selection = Controller::Selection::OnePlayer;

 private:
  Snake snake;
  SDL_Point food;
  bool welcome_window{true};
  bool window_destruction{false};

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int record_score{0};
  std::string record_player{"No one!"};
  
  void RetrieveRecordData();
  void StoreRecordData(std::string &player_name);
  void PlaceFood();
  void Update();
};

#endif