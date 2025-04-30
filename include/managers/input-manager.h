#pragma once

#include <list>
#include <memory>
#include "commands.h"
#include "types.h"

class InputManager {
public:
  InputManager(Registry& registry);
  virtual ~InputManager();

  std::unique_ptr<Command> HandleInput();
  void Update();

private:
  std::list<std::unique_ptr<Command>> history_;
  Registry& registry_;

  float last_move_time_ = 0.0f;
  const float move_cooldown_ = 0.20f;

  Vector2Int GetMoveInput();
};
