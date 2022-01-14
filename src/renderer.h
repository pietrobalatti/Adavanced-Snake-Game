#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "controller.h"
#include <string>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void Render(Controller::Selection const &selection);
  void RenderEndScreen();
  void UpdateWindowTitle(std::string title);

  // Setter
  void setScreenSize(const std::size_t &s_width, const std::size_t &s_height);
  void setGridSize(const std::size_t &g_width, const std::size_t &g_height);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::size_t screen_width;
  std::size_t screen_height;
  std::size_t grid_width;
  std::size_t grid_height;

  void ReadBoardFile(std::string &path, std::vector<SDL_Point> &welcome_msg);
};

#endif