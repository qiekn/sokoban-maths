#include "systems/move-system.h"
#include "commponents/components.h"
#include "constants.h"
#include "types.h"

/**
 * @brief gather allowable moves
 *
 * @param entity
 * @param direction
 * @param count (how many items can be move at once)
 */
bool MoveSystem::TryMove(MoveBuffer& to_move, Entity entity, Vector2Int dir,
                         int push_ability) {
  // get player original position and destination
  auto& pos = registry_.get<Position>(entity);
  Vector2Int dest = pos + dir;
  TraceLog(LOG_DEBUG, "TryMove: %d %d, dir: %d %d", pos.x, pos.y, dir.x, dir.y);
  to_move.emplace_back(entity, dir);  // register self

  // magic move
  // push number to operator box
  bool src_is_number = registry_.all_of<Number>(entity);
  bool dest_is_operator = operator_map_.find(dest) != operator_map_.end();
  if (src_is_number && dest_is_operator) {
    return true;
  }

  // out of map
  if (dest.x < 0 || dest.x >= kCols || dest.y < 0 || dest.y >= kRows) {
    TraceLog(LOG_DEBUG, "TryMove: out of map");
    return false;
  }

  // hit obstacle
  if (immov_map_.find(dest) != immov_map_.end()) {
    TraceLog(LOG_DEBUG, "TryMove: hit obstacle");
    return false;
  }

  // hit movable
  bool hit_movable = mov_map_.find(dest) != mov_map_.end();
  if (hit_movable) {
    if (push_ability > 0) {
      TraceLog(LOG_DEBUG, "TryMove: hit movable");
      Entity other = mov_map_[dest];
      return TryMove(to_move, other, dir, --push_ability);
    }
    return false;
  }

  // hit nothing
  TraceLog(LOG_DEBUG, "TryMove: hit nothing");
  return true;
}

/**
 * @brief can entities move one step
 *
 * @param entities
 * @param dir
 *
 */
MoveBuffer MoveSystem::Move(std::vector<Entity> entities, Vector2Int dir) {
  InitMaps();
  MoveBuffer to_move;
  TraceLog(LOG_DEBUG, "MoveSystem: start");
  // check move for each entity
  for (const auto entity : entities) {
    // now this method only used by player entities
    // skip non-player entity
    if (!registry_.all_of<Player, Position>(entity)) {
      continue;
    }
    if (!TryMove(to_move, entity, dir, 1)) {
      TraceLog(LOG_DEBUG, "MoveSystem: failed");
      return {};
    }
  }
  TraceLog(LOG_DEBUG, "MoveSystem: succeed");
  return to_move;
}

template <typename Component>
void MoveSystem::UpdateMap(Map& map) {
  map.clear();
  auto view = registry_.view<Position, Component>();
  for (auto e : view) {
    const auto& pos = registry_.get<Position>(e);
    map[pos] = e;
  }
}

void MoveSystem::InitMaps() {
  UpdateMap<Movable>(mov_map_);
  UpdateMap<Imovable>(immov_map_);
  UpdateMap<MathOperator>(operator_map_);
}
