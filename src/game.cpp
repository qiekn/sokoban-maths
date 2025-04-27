#include "game.h"
#include <raylib.h>
#include "constants.h"

Game::Game() {
  SetTraceLogLevel(LOG_WARNING);

  camera_.target = (Vector2){kCellSize * kCols * 0.5, kCellSize * kRows * 0.5};
  camera_.offset = (Vector2){kScreenWidth / 2.0f, kScreenHeight / 2.0f};
  camera_.rotation = 0.0f;
  camera_.zoom = 1.0f;

  InitWindow(kScreenWidth, kScreenHeight, "game");
  SetTargetFPS(kFps);
}

Game::~Game() { CloseWindow(); }

void Game::Run() {
  is_running_ = true;
  while (!WindowShouldClose() && is_running_) {
    Update();
    Draw();
  }
}

void Game::Update() {}

void Game::Draw() {
  BeginDrawing();
  BeginMode2D(camera_);

  background_.Draw();

  EndMode2D();
  EndDrawing();
}
