#pragma once

#include "types.h"

class MoveSystem {
public:
  MoveSystem(Registry& registry) : registry_(registry) {}

  void Move(Vector2Int dir);

private:
  Registry& registry_;
};
