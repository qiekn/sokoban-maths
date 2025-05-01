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
  Map mov_map_;
  Map immov_map_;
  Map operator_map_;

  void InitMaps();

  bool TryMove(MoveBuffer& to_move, Entity entity, Vector2Int dir, int count);

  template <typename Component>
  void UpdateMap(Map& map);
};
