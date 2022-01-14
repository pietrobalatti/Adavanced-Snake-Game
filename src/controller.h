#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:

  enum class Selection { Easy = 0, Std, Hard, Enter };

  void HandleInput(bool &running, Snake &snake) const;
  void HandleInput(bool &running, Selection &selection) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif