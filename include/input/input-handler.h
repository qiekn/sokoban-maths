#pragma once

#include <list>
#include <memory>
#include "input/commands.h"
#include "types.h"

class InputHandler {
public:
  InputHandler(Registry& registry);
  virtual ~InputHandler();

  std::unique_ptr<Command> HandleInput();
  void Update();

private:
  Registry& registry_;
  std::list<std::unique_ptr<Command>> history_;

  float last_move_time_ = 0.0f;
  const float move_cooldown_ = 0.08f;
};
