#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include "entities/prefabs.h"
#include "types.h"

enum class TileType {
  kNumber,
  kSprite = 10000,
  kFloor,
  kPlayer,
  kWall,
  kOperator = 20000,
  kAdd,
  kSub,
  kMul,
  kDiv,
  kTarget = 30000,
};

struct LevelData {
  std::string name;
  int width;
  int height;
  std::vector<std::vector<TileType>> map;
};

class LevelManager {
public:
  explicit LevelManager(Registry& registry, Prefabs& prefabs)
      : current_level_(0), registry_(registry), prefabs_(prefabs) {}

  /** @brief load level data from json files */
  void LoadJson();

  void SetLevel(int index);

  /** @brief used to choose level */
  void InitLevel(int index);

  /** @brief init current level */
  void InitLevel();

  void NextLevel();

  void PrevLevel();

private:
  int current_level_;
  std::vector<LevelData> levels_;
  Registry& registry_;
  Prefabs prefabs_;
};
