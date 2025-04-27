#pragma once

#include <raylib.h>
#include "background.h"

class Game {
 public:
  Game();
  virtual ~Game();
  void Run();

 private:
  bool is_running_ = false;
  Background background_ = Background();
  Camera2D camera_ = {0};

  void Update();
  void Draw();
};
