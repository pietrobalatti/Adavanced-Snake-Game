#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
}

void Controller::HandleInput(bool &running, Selection &selection) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_DOWN:
          switch(selection) {
            case Selection::Easy:
              selection = Selection::Std;
              break;
            case Selection::Std:
              selection = Selection::Hard;
              break;
            case Selection::Hard:
              selection = Selection::Easy;
              break;
          }
          break;
        case SDLK_UP:
          switch(selection) {
            case Selection::Easy:
              selection = Selection::Hard;
              break;
            case Selection::Std:
              selection = Selection::Easy;
              break;
            case Selection::Hard:
              selection = Selection::Std;
              break;
          }
          break;
        case SDLK_RETURN:
        case SDLK_KP_ENTER:
            selection = Selection::Enter;
            break;
      }
    }
  }
}