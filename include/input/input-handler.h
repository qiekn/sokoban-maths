#pragma once

#include <list>
#include <memory>
#include "input/commands.h"

class InputHandler {
public:
  InputHandler();
  virtual ~InputHandler();

  std::unique_ptr<Command> HandleInput();
  void Update();

private:
  std::list<std::unique_ptr<Command>> history_;

  float last_move_time_ = 0.0f;
  const float move_cooldown_ = 0.20f;
};
