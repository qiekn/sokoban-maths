#include "entities/prefabs.h"
#include <raylib.h>
#include "commponents/components.h"
#include "entt.h"

Prefabs::Prefabs(Registry& registry) : registry_(registry) {}

Prefabs::~Prefabs() {}

void Prefabs::CreatePlayer(Position pos) {
  auto entity = registry_.create();
  registry_.emplace<Player>(entity);
  registry_.emplace<Position>(entity, pos);
  auto sprite_renderer = SpriteRenderer{
      .color = BLUE,
      .text = "P",
      .type = SpriteType::kFill,
  };
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
}

void Prefabs::CreateBox(Position pos) {
  auto entity = registry_.create();
  registry_.emplace<Box>(entity);
  registry_.emplace<Position>(entity, pos);
  auto sprite_renderer = SpriteRenderer{
      .color = YELLOW,
      .text = "B",
      .type = SpriteType::kFill,
  };
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
}

void Prefabs::CreateWall(Position pos) {
  auto entity = registry_.create();
  registry_.emplace<Wall>(entity);
  registry_.emplace<Position>(entity, pos);
  auto sprite_renderer = SpriteRenderer{
      .color = GRAY,
      .text = "W",
      .type = SpriteType::kFill,
  };
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
}

void Prefabs::CreateFloor(Position pos) {
  auto entity = registry_.create();
  registry_.emplace<Wall>(entity);
  registry_.emplace<Position>(entity, pos);
}

void Prefabs::CraeteNumber(Position pos, int val) {
  auto entity = registry_.create();
  registry_.emplace<Number>(entity, val);
  registry_.emplace<Position>(entity, pos);
}

void Prefabs::CreateOperator(Position pos) {
  auto entity = registry_.create();
  /* todo */
  registry_.emplace<Position>(entity, pos);
}

void Prefabs::CreateTarget(Position pos, int value) {
  auto entity = registry_.create();
  registry_.emplace<Target>(entity);
  registry_.emplace<Position>(entity, pos);
}
