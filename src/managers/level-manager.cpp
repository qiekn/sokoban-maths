#include "managers/level-manager.h"
#include <filesystem>
#include <fstream>
#include <string>
#include "commponents/components.h"
#include "constants.h"
#include "json.h"

void LevelManager::LoadJson() {
  TraceLog(LOG_DEBUG, "LevelManager: Load Json");
  std::filesystem::path path = kLevels / "level-test.json";
  std::ifstream file(path);
  if (!file.is_open()) {
    TraceLog(LOG_ERROR, "failed to open level file: %s", path.c_str());
  }

  nlohmann::json leveldata;
  file >> leveldata;

  auto metadata = leveldata["metadata"];
  int width = metadata["width"];
  int height = metadata["height"];

  auto map = leveldata["map"].get<std::vector<std::vector<std::string>>>();

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      const std::string& type = map[y][x];
      auto pos = Position{x, y};
      // clang-format off
      if (type == "W")  prefabs_.CreateWall(pos);
      else if (type == "P")  prefabs_.CreatePlayer(pos);
      else if (type == ".")  prefabs_.CreateFloor(pos);
      else if (type == "+")  prefabs_.CreateOperatorAdd(pos);
      else if (type == "-")  prefabs_.CreateOperatorSub(pos);
      else if (type == "*")  prefabs_.CreateOperatorMul(pos);
      else if (type == "/")  prefabs_.CreateOperatorDiv(pos);
      // clang-format on
    }
  }

  // numbers
  auto numbers = leveldata["numbers"];
  for (const auto& number : numbers) {
    int x = number["x"];
    int y = number["y"];
    int value = number["value"];
    auto pos = Position{x, y};
    prefabs_.CreateNumber(pos, value);
  }

  // targets
  auto targets = leveldata["targets"];
  for (const auto& target : targets) {
    int x = target["x"];
    int y = target["y"];
    int requiredValue = target["requiredValue"];
    auto pos = Position{x, y};
    prefabs_.CreateTarget(pos, requiredValue);
  }
}

void LevelManager::InitLevel() {}

void LevelManager::SetLevel(int index) {
  if (index >= 0 && index < levels_.size()) {
    current_level_ = index;
  } else {
    TraceLog(LOG_ERROR, "level index: %d is out of range!", index);
  }
}

void LevelManager::InitLevel(int index) {
  SetLevel(index);
  InitLevel();
}

void LevelManager::NextLevel() {
  SetLevel(current_level_ + 1);
  InitLevel();
}

void LevelManager::PrevLevel() {
  SetLevel(current_level_ - 1);
  InitLevel();
}
