#pragma once

#include "utils/IO.h"
#include <chrono>
#include <stdexcept>

class Game {
public:
  Game() = default;

  void start();

protected:
  virtual bool updateFrame() = 0;
};