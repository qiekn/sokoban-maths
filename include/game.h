#pragma once

#include <raylib.h>

class Game {
public:
  Game();
  void Run();

private:
  bool is_running_ = false;
  Camera2D camera_ = {0};

  /* method */
  void Update();
  void Draw();
};
