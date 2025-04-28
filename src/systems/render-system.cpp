#include "systems/render-system.h"
#include <raylib.h>
#include "components.h"

void RenderSystem::Draw() {
  // draw bg
  DrawBackground();
  DrawGrid();
  // draw entities
  auto view = registry_.view<Position, Renderable>();
  for (auto entity : view) {
    const auto& pos = view.get<Position>(entity);
    const auto& render = view.get<Renderable>(entity);
    float px = pos.x * kCellSize;
    float py = pos.y * kCellSize;
    if (render.fill) {
      DrawRectangle(px, py, kCellSize, kCellSize, render.color);
    } else {
      DrawRectangleLines(px, py, kCellSize, kCellSize, render.color);
    }

    if (!render.text.empty()) {
      DrawText(render.text.c_str(), px + kCellSize * 0.5, py + kCellSize * 0.5, 20, WHITE);
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
