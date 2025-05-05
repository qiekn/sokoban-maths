#include "systems/render-system.h"
#include <raylib.h>
#include <string>
#include "commponents/components.h"
#include "constants.h"
#include "imgui.h"
#include "maid.h"
#include "managers/texture-manager.h"
#include "rlimgui.h"
#include "types.h"
#include "utils.h"

RenderSystem::RenderSystem() {}

void RenderSystem::DrawScene() {
  DrawBackground();
  DrawGrid();
  DrawEntities();
  DrawNumbers();
}

void RenderSystem::DrawUI() { DrawImGui(); }

void RenderSystem::DrawBackground() {
  auto background_outer = Color{38, 30, 67, 255};
  auto background_inner = Color{26, 19, 35, 255};
  ClearBackground(background_outer);
  auto height = kCellSize * kRows;
  auto width = kCellSize * kCols;
  DrawRectangle(0, 0, width, height, background_inner);
}

void RenderSystem::DrawGrid() {
  int scale = 1;
  int sz = kCellSize * scale;
  Color color = Color{47, 34, 86, 255};

  // horizontal lines
  for (int i = 0; i <= kRows; i++) {
    DrawLine(0, i * sz, kCols * sz, i * sz, color);
  }

  // vertical lines
  for (int i = 0; i <= kCols; i++) {
    DrawLine(i * sz, 0, i * sz, kRows * sz, color);
  }
}

void RenderSystem::DrawEntities() {
  auto view = Maid::Instance().registry_.view<Position, SpriteRenderer>(
      entt::exclude<Disable>);
  for (auto entity : view) {
    const auto& pos = view.get<Position>(entity);
    const auto& render = view.get<SpriteRenderer>(entity);
    float px = pos.x * kCellSize;
    float py = pos.y * kCellSize;

    // clang-format off
    switch (render.type) {
      case SpriteType::kOutline:
        DrawRectangleLines(px + kCellOffset, py + kCellOffset, kCellSizeInner, kCellSizeInner, render.color);
        break;
      case SpriteType::kFill:
        DrawRectangle(px + kCellOffset, py + kCellOffset, kCellSizeInner, kCellSizeInner, render.color);
        break;
      case SpriteType::kFull:
        DrawRectangle(px, py, kCellSize, kCellSize, render.color);
        break;
      case SpriteType::kText:
        DrawRectangle(px, py, kCellSize, kCellSize, render.color);
        if (!render.text.empty()) {
          HelperDrawText(render.text.c_str(), pos, WHITE);
        }
        break;
      case SpriteType::kTexture:
        /* texture */
        if (!render.path.empty()) {
          Texture2D& texture = TextureManager::Instance().GetTexture(render.path);
          DrawTexture(texture, px, py, WHITE);
        }
        break;
      default:
        break;
    }
    // clang-format on

    // always draw outline
    DrawRectangleLines(px, py, kCellSize, kCellSize, kBorderColor);
  }
}

void RenderSystem::DrawNumbers() {
  auto view =
      Maid::Instance().registry_.view<Position, Number>(entt::exclude<Disable>);
  for (auto entity : view) {
    const auto& pos = view.get<Position>(entity);
    const auto& number = view.get<Number>(entity);

    auto text = std::to_string(number.value);
    HelperDrawText(text.c_str(), pos, WHITE);
  }
}

void RenderSystem::DrawImGui() {
  rlImGuiBegin();

  bool open = true;
  ImGui::ShowDemoWindow(&open);

  rlImGuiEnd();
}

void RenderSystem::HelperDrawText(const char* text, Position pos, Color color) {
  int text_width = MeasureText(text, kFontSize);
  int text_height = kFontSize;
  auto world_pos = GridToWorld(pos);
  float center_x = world_pos.x + kCellSize * 0.5f - text_width * 0.5f;
  float center_y = world_pos.y + kCellSize * 0.5f - text_height * 0.5f;
  DrawText(text, center_x, center_y, kFontSize, WHITE);
}
