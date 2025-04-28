#pragma once

#include <raylib.h>
#include <filesystem>
#include <functional>
#include <string>

enum class BoxType {
  kWall,
  kPlayer,
  kMovable,
  kNumber,
  kOperator,
  kMathBox,
  kTarget,
};

enum class SpriteBorderType {
  kNone,
  kOutline,
  kFill,
};

struct Position {
  int x, y;
};

struct SpriteRenderer {
  Color color = BLANK;
  std::string text = "";               // text to display (e.g. number, symbol)
  std::filesystem::path texture_path;  // texture path
  SpriteBorderType border_type = SpriteBorderType::kNone;
};

struct Value {
  int value;
};

struct MathOperator {
  char symbol;  // "+" "-" "*" "/"
  std::function<int(int, int)> operation;
  bool has_operand;
};

struct Target {
  int target_value;
  bool satisfied;
};
