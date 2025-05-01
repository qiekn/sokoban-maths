#pragma once

#include <raylib.h>
#include "commponents/components.h"
#include "entt.h"

class RenderSystem {
public:
  RenderSystem();
  void Draw();

private:
  void DrawBackground();
  void DrawGrid();
  void DrawEntities();
  void DrawNumbers();

  void HelperDrawText(const char* text, Position pos, Color color);
};
