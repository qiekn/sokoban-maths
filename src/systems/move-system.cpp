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
bool TryMove(Registry& registry, Map& mov, Map& immov, MoveBuffer& to_move,
             Entity entity, Vector2Int dir, int count) {
  // get player original position and destination
  auto& pos = registry.get<Position>(entity);
  Vector2Int dest = pos + dir;

  // hit obstacle
  if (immov.find(dest) != immov.end()) {
    TraceLog(LOG_DEBUG, "TryMove: (%d %d) Hit Obstacle", pos.x + 1, pos.y + 1);
    return false;
  }

  // check map border
  if (dest.x < 0 || dest.x >= kCols || dest.y < 0 || dest.y >= kRows) {
    return false;
  }

  // register self
  to_move.emplace_back(entity, dir);

  // hit movable item, recur trymove other
  if (mov.find(dest) != mov.end()) {
    if (count >= 1) {
      Entity other = mov[dest];
      return TryMove(registry, mov, immov, to_move, other, dir, --count);
    }
    // can't push bacause of no 'count' left
    return false;
  }

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
  MoveBuffer to_move;

  // gather mappings
  Map mov_map;    // movable boxes map
  Map immov_map;  // immovable boxes map
  auto mov_view = registry_.view<Position, Movable>();
  for (auto e : mov_view) {
    auto& pos = registry_.get<Position>(e);
    mov_map[pos] = e;
  }
  auto immov_view = registry_.view<Position, Imovable>();
  for (auto e : immov_view) {
    auto& pos = registry_.get<Position>(e);
    immov_map[pos] = e;
  }

  // check move for each entity
  for (const auto entity : entities) {
    // now this method only used by player entities
    // skip non-player entity
    if (!registry_.all_of<Player, Position>(entity)) {
      continue;
    }
    if (!TryMove(registry_, mov_map, immov_map, to_move, entity, dir, 1)) {
      return {};
    }
  }
  return to_move;
}
