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
  kFull,
  kText,  // text with squire colored background
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
  int value;
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
  std::string op;                          // display symbol
  std::function<int(int, int)> calculate;  // storage operation logic
  int value = 0;
};

struct Target {
  int target_value;
  bool satisfied;
};

struct Movable {};

struct Imovable {};

// ignored by render system
struct Disable {};
