#pragma once

#include "types.h"

class MoveSystem {
public:
  explicit MoveSystem(Registry& registry, Map& entity_map)
      : registry_(registry), entity_map_(entity_map) {}

  void Move(Vector2Int dir);

private:
  Registry& registry_;
  Map& entity_map_;
};
