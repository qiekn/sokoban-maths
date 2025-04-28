#pragma once

#include "entt.h"
#include "types.h"

class RenderSystem {
public:
  explicit RenderSystem(Registry& registry) : registry_(registry) {}
  void Draw();

private:
  Registry& registry_;

  void DrawBackground();
  void DrawGrid();
};
