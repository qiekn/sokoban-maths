#pragma once

#include <utility>

const int kCellSize = 50;
const int kRows = 18;
const int kCols = 22;
const int kCellsPerRow = kCols;
const int kCellsPerColumn = kRows;
const int kScreenBorder = 1 * kCellSize;

const int kScreenWidth = static_cast<int>(kCellSize * kCols + kScreenBorder);
const int kScreenHeight = static_cast<int>(kCellSize * kRows + kScreenBorder);
const auto kScreenTitle = "game";

const int kFps = 60;

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
