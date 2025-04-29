#include "systems/move-system.h"
#include <vector>
#include "components.h"
#include "managers/maid.h"
#include "types.h"

void MoveSystem::Move(Vector2Int dir) {
  // find player entities
  std::vector<entt::entity> players;
  auto player_view = Maid::Instance().registry_.view<BoxType, Position>();
  for (auto entity : player_view) {
    if (player_view.get<BoxType>(entity) == BoxType::kPlayer) {
      auto pos = player_view.get<Position>(entity);
      players.push_back(entity);
    }
  }
}
