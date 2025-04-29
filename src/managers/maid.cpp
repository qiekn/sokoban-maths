#include "managers/maid.h"
#include "components.h"
#include "constants.h"
#include "types.h"

Maid::Maid() : rows_(kRows), cols_(kCols) {}

void Maid::Register(Entity entity) {
  auto& pos = registry_.get<Position>(entity);
  entity_map_[{pos.x, pos.y}] = entity;
}

void Maid::Unregister(Entity entity) {
  auto& pos = registry_.get<Position>(entity);
  if (entity_map_.find({pos.x, pos.y}) != entity_map_.end()) {
    entity_map_.erase({pos.x, pos.y});
  }
}

Entity Maid::GetEntity(int x, int y) { return entity_map_[{x, y}]; }

Entity Maid::GetEntity(Vector2Int pos) { return entity_map_[{pos.x, pos.y}]; }

template <typename T>
std::optional<T> Maid::GetComponent(int x, int y) {
  auto entity = GetEntity(x, y);
  if (entity != entt::null && registry_.all_of<T>(entity)) {
    return registry_.get<T>(entity);
  }
  return std::nullopt;
}

template <typename T>
std::optional<T> Maid::GetComponent(Vector2Int pos) {
  return GetComponent<T>(pos.x, pos.y);
}
