#include "renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(Controller::Selection const &selection) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render message
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

  // TODO: Move this somewhere else
  // Build welcome msg, extracted from a 20x20 grid
  std::vector<SDL_Point> welcome_msg;
  std::string file_path{"../data/welcome_msg.grid"};
  ReadBoardFile(file_path, welcome_msg);

  int offset_x = grid_width/2 - 10;
  int offset_y = grid_width/2 - 10;

  for (SDL_Point const &point : welcome_msg) {
    block.x = (offset_x + point.x) * block.w;
    block.y = (offset_y + point.y) * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render selection
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  switch(selection) {
    case Controller::Selection::Easy:
      block.x = (offset_x - 2) * block.w;
      block.y = (offset_y + 3) * block.h;
      break;
    case Controller::Selection::Std:
      block.x = (offset_x - 2) * block.w;
      block.y = (offset_y + 9) * block.h;
      break;
    case Controller::Selection::Hard:
      block.x = (offset_x - 2) * block.w;
      block.y = (offset_y + 15) * block.h;
      break;
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderEndScreen() {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render message
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

  // TODO: Move this somewhere else
  // Build welcome msg, extracted from a 20x20 grid
  std::vector<SDL_Point> end_msg;
  std::string file_path{"../data/end_msg.grid"};
  ReadBoardFile(file_path, end_msg);

  int offset_x = grid_width/2 - 10;
  int offset_y = grid_width/2 - 10;

  for (SDL_Point const &point : end_msg) {
    block.x = (offset_x + point.x) * block.w;
    block.y = (offset_y + point.y) * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(std::string title) {
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::ReadBoardFile(std::string &path, std::vector<SDL_Point> &welcome_msg) {
  std::ifstream msg_file;
  int n;
  int raw{0};
  int col{0};
  msg_file.open(path);
  if (msg_file) {
    std::string line;
    while (getline(msg_file, line)) {
      // std::cout << "line " << raw << ": " << line << "\n";
      // Line parsing
      std::istringstream sline(line);
      while (sline >> n) {
        // If point is one, push into vector
        if (n == 1) {
          SDL_Point point{col,raw};
          welcome_msg.push_back(point);
        }
        col++;
      }
      // Reset col and increase raw
      col = 0;
      raw++;
    }
  }
}

void Renderer::setScreenSize(const std::size_t &s_width, const std::size_t &s_height) {
  this->screen_width = s_width;
  this->screen_height = s_height;
  SDL_SetWindowSize(sdl_window, screen_width, screen_height);
  SDL_SetWindowPosition(sdl_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Renderer::setGridSize(const std::size_t &g_width, const std::size_t &g_height) {
  this->grid_width = g_width;
  this->grid_height = g_height;
}
