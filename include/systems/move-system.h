#pragma once

#include <vector>
#include "types.h"

using MoveBuffer = std::vector<std::pair<Entity, Vector2Int>>;

class MoveSystem {
public:
  MoveSystem(Registry& registry) : registry_(registry) {}

  MoveBuffer Move(std::vector<Entity> entities, Vector2Int dir);

private:
  Registry& registry_;
};
