#pragma once

#include "entt.h"

class RenderSystem {
public:
  RenderSystem();
  void Draw();

private:
  void DrawBackground();
  void DrawGrid();
};
