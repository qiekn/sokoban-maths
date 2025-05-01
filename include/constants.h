#pragma once

#include <raylib.h>
#include <filesystem>
#include <utility>
#include "utils.h"

const std::filesystem::path kAssets = SOKOBAN_ASSETS;
const std::filesystem::path kLevels = SOKOBAN_LEVELS;

const int kFontSize = 20;  // inner box text
const Color kBackgroundOuter = Haxc("#261e43");
const Color kBackgroundInner = Haxc("#1a1323");

const Color kGridColor = Color{47, 34, 86, 255};
const Color kBorderColor = kGridColor;  // cell border outline color

namespace OperatorColor {
const Color kBlue = Haxc("#7da2a8");
const Color kYellow = Haxc("#e1d6a0");
const Color kPink = Haxc("#cb94b4");
const Color kViolet = Haxc("#675ab3");
}  // namespace OperatorColor

enum class OperatorType {
  kAdd,
  kSub,
  kMul,
  kDiv,
};

const int kCellSize = 50;
const int kCellOffset = 3;
const int kCellSizeInner = kCellSize - 2 * kCellOffset;

const int kRows = 18;
const int kCols = 22;
const int kCellsPerRow = kCols;
const int kCellsPerColumn = kRows;
const int kScreenBorder = 1 * kCellSize;

const int kScreenWidth = static_cast<int>(kCellSize * kCols + kScreenBorder);
const int kScreenHeight = static_cast<int>(kCellSize * kRows + kScreenBorder);
const auto kScreenTitle = "game";

const int kFps = 60;

const int kMaxUndoHistry = 50;

enum class Direction {
  kNone = 0,
  kUp,
  kDown,
  kLeft,
  kRight,
};

// hash function for std::pair<int, int> to use in unordered_map.
struct PairHash {
  template <typename T1, typename T2>
  std::size_t operator()(const std::pair<T1, T2>& pair) const {
    return std::hash<T1>{}(pair.first) ^ std::hash<T2>{}(pair.second);
  }
};
