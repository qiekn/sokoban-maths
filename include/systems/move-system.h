#pragma once

#include <vector>
#include "types.h"

using MoveBuffer = std::vector<std::pair<Entity, Vector2Int>>;

class MoveSystem {
public:
  MoveSystem(Registry& registry, Dispatcher& dispatcher)
      : registry_(registry), dispatcher_(dispatcher) {}

  MoveBuffer Move(std::vector<Entity> entities, Vector2Int dir);

private:
  void InitMaps();

  bool TryMove(MoveBuffer& to_move, Entity entity, Vector2Int dir, int count);

  template <typename Component>
  void UpdateMap(Map& map);

private:
  Registry& registry_;
  Dispatcher& dispatcher_;
  Map mov_map_;
  Map immov_map_;
  Map operator_map_;
};
