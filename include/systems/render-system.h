#pragma once

#include <raylib.h>
#include "commponents/components.h"
#include "entt.h"

class RenderSystem {
public:
  RenderSystem();
  void DrawScene();
  void DrawUI();

private:
  // scene
  void DrawBackground();
  void DrawGrid();
  void DrawEntities();
  void DrawNumbers();

  // ui
  void DrawImGui();

  // helper functions
  void HelperDrawText(const char* text, Position pos, Color color);
};
