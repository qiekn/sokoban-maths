#include "game.h"
#include <raylib.h>
#include "constants.h"
#include "input/input-handler.h"
#include "level.h"

Game::Game()
    : render_system_(registry_),
      input_system_(registry_),
      move_system_(registry_, entity_map_),
      win_condition_system_(registry_),
      level_manager_(registry_, entity_map_) {}

void Game::Run() {
  // SetTraceLogLevel(LOG_WARNING);
  SetTraceLogLevel(LOG_DEBUG);

  camera_.target = (Vector2){kCellSize * kCols * 0.5, kCellSize * kRows * 0.5};
  camera_.offset = (Vector2){kScreenWidth / 2.0f, kScreenHeight / 2.0f};
  camera_.rotation = 0.0f;
  camera_.zoom = 1.0f;

  InitWindow(kScreenWidth, kScreenHeight, "game");
  SetTargetFPS(kFps);
  is_running_ = true;
  level_manager_.LoadLevelDatas();
  level_manager_.LoadCurrentLevel();
  while (!WindowShouldClose() && is_running_) {
    Update();
    Draw();
  }
}

void Game::Update() { input_system_.Update(); }

void Game::Draw() {
  BeginDrawing();
  BeginMode2D(camera_);

  render_system_.Draw();

  EndMode2D();
  EndDrawing();
}
