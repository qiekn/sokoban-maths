#pragma once

#include <raylib.h>
#include <filesystem>
#include <functional>
#include <string>
#include "types.h"

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

  void MoveTo(Vector2Int dest) { x = dest.x, y = dest.y; };
  void MoveTo(int _x, int _y) { x = _x, y = _y; }
};

struct Player {};

struct Wall {};

struct Box {};

struct Number {
  int val;
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
