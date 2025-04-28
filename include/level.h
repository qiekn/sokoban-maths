#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include "types.h"

struct LevelData {
  std::string name;
  std::vector<std::string> layout;
};

class LevelManager {
public:
  explicit LevelManager(Registry& registry, Map& map)
      : current_level_(0), registry_(registry), entity_map_(map) {}

  void LoadLevelDatas();

  void SetLevel(int index);
  void LoadLevel(int index);
  void LoadCurrentLevel();
  void Next();
  void Prev();

private:
  int current_level_;
  std::vector<LevelData> levels_;
  Registry& registry_;
  Map& entity_map_;
};
