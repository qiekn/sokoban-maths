#include "entities/prefabs.h"
#include <raylib.h>
#include "commponents/components.h"
#include "constants.h"
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
  registry_.emplace<Imovable>(entity);
  auto sprite_renderer = SpriteRenderer{
      .color = kBackgroundOuter,
      .text = "",
      .type = SpriteType::kFull,
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
  registry_.emplace<Movable>(entity);
}

// Operators

void Prefabs::CreateOperatorAdd(Position pos) {
  auto entity = registry_.create();
  auto add = [](int a, int b) { return a + b; };
  auto sprite_renderer = SpriteRenderer{
      .path = kAssets / "sprites/add.png",
      .type = SpriteType::kTexture,
  };
  registry_.emplace<MathOperator>(entity, "+", add);
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
  registry_.emplace<Position>(entity, pos);
  registry_.emplace<Movable>(entity);
}

void Prefabs::CreateOperatorSub(Position pos) {
  auto entity = registry_.create();
  auto sub = [](int a, int b) { return a - b; };
  auto sprite_renderer = SpriteRenderer{
      .path = kAssets / "sprites/sub.png",
      .type = SpriteType::kTexture,
  };
  registry_.emplace<MathOperator>(entity, "+", sub);
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
  registry_.emplace<Position>(entity, pos);
  registry_.emplace<Movable>(entity);
}

void Prefabs::CreateOperatorMul(Position pos) {
  auto entity = registry_.create();
  auto mul = [](int a, int b) { return a * b; };
  auto sprite_renderer = SpriteRenderer{
      .path = kAssets / "sprites/mul.png",
      .type = SpriteType::kTexture,
  };
  registry_.emplace<MathOperator>(entity, "+", mul);
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
  registry_.emplace<Position>(entity, pos);
  registry_.emplace<Movable>(entity);
}

void Prefabs::CreateOperatorDiv(Position pos) {
  auto entity = registry_.create();
  auto div = [](int a, int b) { return a / b; };
  auto sprite_renderer = SpriteRenderer{
      .path = kAssets / "sprites/div.png",
      .type = SpriteType::kTexture,
  };
  registry_.emplace<MathOperator>(entity, "+", div);
  registry_.emplace<SpriteRenderer>(entity, sprite_renderer);
  registry_.emplace<Position>(entity, pos);
  registry_.emplace<Movable>(entity);
}

void Prefabs::CreateOperator(Position pos) {
  auto entity = registry_.create();
  /* todo */
  registry_.emplace<Position>(entity, pos);
}

// Targets

void Prefabs::CreateTarget(Position pos, int value) {
  auto entity = registry_.create();
  registry_.emplace<Target>(entity);
  registry_.emplace<Position>(entity, pos);
}
