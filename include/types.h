#pragma once

#include "constants.h"
#include "entt.h"

using Registry = entt::registry;
using Map = std::unordered_map<std::pair<int, int>, entt::entity, PairHash>;

struct Vector2Int {
  int x, y;
};
