#include "game.h"
#include <raylib.h>
#include "constants.h"
#include "imgui.h"
#include "maid.h"
#include "rlimgui.h"

Game::Game() {}

void Game::Run() {
  // SetTraceLogLevel(LOG_WARNING);
  SetTraceLogLevel(LOG_DEBUG);
  DrawFPS(0, 0);

  camera_.target = (Vector2){kCellSize * kCols * 0.5, kCellSize * kRows * 0.5};
  camera_.offset = (Vector2){kScreenWidth / 2.0f, kScreenHeight / 2.0f};
  camera_.rotation = 0.0f;
  camera_.zoom = 1.0f;

  InitWindow(kScreenWidth, kScreenHeight, "game");
  SetTargetFPS(kFps);
  is_running_ = true;

  // ImGui
  rlImGuiSetup(true);
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.FontGlobalScale = 1.25f;
  ImGui::StyleColorsClassic();

  Maid::Instance().level_manager_.LoadJson();
  Maid::Instance().level_manager_.InitLevel();

  while (!WindowShouldClose() && is_running_) {
    Update();
    Draw();
  }
}

void Game::Update() { Maid::Instance().input_manager.Update(); }

void Game::Draw() {
  BeginDrawing();

  BeginMode2D(camera_);
  Maid::Instance().render_system_.DrawScene();
  EndMode2D();

  Maid::Instance().render_system_.DrawUI();

  EndDrawing();
}
