#include "systems/render-system.h"
#include <raylib.h>
#include "commponents/components.h"
#include "constants.h"
#include "maid.h"
#include "managers/texture-manager.h"

RenderSystem::RenderSystem() {}

void RenderSystem::Draw() {
  // draw bg
  DrawBackground();
  DrawGrid();
  // draw entities
  auto view = Maid::Instance().registry_.view<Position, SpriteRenderer>();
  for (auto entity : view) {
    const auto& pos = view.get<Position>(entity);
    const auto& render = view.get<SpriteRenderer>(entity);
    float px = pos.x * kCellSize;
    float py = pos.y * kCellSize;

    /* texture */
    if (!render.path.empty()) {
      Texture2D& texture = TextureManager::Instance().GetTexture(render.path);
      DrawTexture(texture, px, py, WHITE);
      DrawRectangleLines(px, py, kCellSize, kCellSize, kBorderColor);
    }

    /* border type */
    if (render.type == SpriteType::kFill) {
      DrawRectangle(px + kCellOffset, py + kCellOffset, kCellSizeInner,
                    kCellSizeInner, render.color);
    } else if (render.type == SpriteType::kOutline) {
      DrawRectangleLines(px + kCellOffset, py + kCellOffset, kCellSizeInner,
                         kCellSizeInner, render.color);
    }

    /* text */
    if (!render.text.empty()) {
      int text_width = MeasureText(render.text.c_str(), kFontSize);
      int text_height = kFontSize;
      float center_x = px + kCellSize * 0.5f - text_width * 0.5f;
      float center_y = py + kCellSize * 0.5f - text_height * 0.5f;
      DrawText(render.text.c_str(), center_x, center_y, kFontSize, WHITE);
    }
  }
}

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
