#pragma once

#include <raylib.h>
#include "background.h"
#include "level.h"
#include "systems/move-system.h"
#include "systems/render-system.h"
#include "systems/win-condition-system.h"
#include "types.h"

class Game {
public:
  Game();
  void Run();

private:
  /* data */
  Registry registry_;
  Map entity_map_;

  bool is_running_ = false;
  Background background_ = Background();
  Camera2D camera_ = {0};

  /* systems */
  LevelManager level_manager_;
  RenderSystem render_system_;
  MoveSystem move_system_;
  WinConditionSystem win_condition_system_;

  /* method */
  void Update();
  void Draw();
};
