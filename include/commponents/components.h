#pragma once

#include <raylib.h>
#include <filesystem>
#include <functional>
#include <string>
#include "types.h"

enum class SpriteType {
  kNone,
  kOutline,
  kFill,
  kTexture,
};

struct Position : public Vector2Int {
  Position() : Vector2Int() {}
  Position(int x, int y) : Vector2Int(x, y) {}
};

struct Player {};

struct Wall {};

struct Box {};

struct Number {
  int val;
};

struct SpriteRenderer {
  Color color = BLANK;
  std::string text = "";       // text to display (e.g. number, symbol)
  std::filesystem::path path;  // texture path
  SpriteType type = SpriteType::kNone;
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

struct Movable {};

struct Imovable {};
