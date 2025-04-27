#include "background.h"
#include <raylib.h>
#include "constants.h"

void Background::Draw() {
  DrawBackground();
  DrawGrid();
}

void Background::DrawBackground() {
  auto background_outer = Color{38, 30, 67, 255};
  auto background_inner = Color{26, 19, 35, 255};
  ClearBackground(background_outer);
  auto height = kCellSize * kRows;
  auto width = kCellSize * kCols;
  DrawRectangle(0, 0, width, height, background_inner);
}

void Background::DrawGrid() {
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
