#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <memory>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Instantiated as unique pointer to destroyed at the end
  auto renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, *renderer, kMsPerFrame);

  // After 2 seconds window will get destroyed
  renderer.reset();

  game.End();
  return 0;
}