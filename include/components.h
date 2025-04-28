#pragma once

#include <raylib.h>
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

struct Position {
  int x, y;
};

struct Renderable {
  Color color;
  std::string text;  // text to display (e.g. number, symbol)
  bool fill;         // fill rectangle or draw outline
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
