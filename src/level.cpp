#include "level.h"
#include "components.h"

void LevelManager::LoadLevelDatas() {
  // TODO: Load levels from file <2025-04-28 18:33, @qiekn> //
  LevelData level_data;
  level_data.name = "Tutorial 1";
  level_data.layout = {"##########", "#  $     #", "#  2 + a #", "#  3 * b #", "##########"};
  levels_.push_back(level_data);
}

void LevelManager::LoadCurrentLevel() {
  // clear existing entities
  registry_.clear();
  entity_map_.clear();
  LevelData data = levels_[current_level_];

  // initialize map
  int rows = data.layout.size();
  int cols = data.layout[0].size();
  std::vector<std::vector<char>> map(rows, std::vector<char>(cols, ' '));
  for (size_t y = 0; y < rows; ++y) {
    for (size_t x = 0; x < cols; ++x) {
      map[y][x] = data.layout[y][x];
      entt::entity entity = registry_.create();
      Position pos{static_cast<int>(x), static_cast<int>(y)};
      registry_.emplace<Position>(entity, pos);
      entity_map_[{x, y}] = entity;

      switch (map[y][x]) {
        case '#':
          registry_.emplace<BoxType>(entity, BoxType::kWall);
          registry_.emplace<Renderable>(entity, Renderable{DARKGRAY, "", true});
          break;
        case '$':
          registry_.emplace<BoxType>(entity, BoxType::kPlayer);
          registry_.emplace<Renderable>(entity, Renderable{BROWN, "", true});
          break;
        case '+':
          registry_.emplace<BoxType>(entity, BoxType::kMathBox);
          registry_.emplace<MathOperator>(
              entity, MathOperator{'+', [](int a, int b) { return a + b; }, false});
          registry_.emplace<Renderable>(entity, Renderable{SKYBLUE, "+", true});
          break;
        case '-':
          registry_.emplace<BoxType>(entity, BoxType::kMathBox);
          registry_.emplace<MathOperator>(
              entity, MathOperator{'-', [](int a, int b) { return a - b; }, false});
          registry_.emplace<Renderable>(entity, Renderable{SKYBLUE, "-", true});
          break;
        case '*':
          registry_.emplace<BoxType>(entity, BoxType::kMathBox);
          registry_.emplace<MathOperator>(
              entity, MathOperator{'*', [](int a, int b) { return a * b; }, false});
          registry_.emplace<Renderable>(entity, Renderable{SKYBLUE, "*", true});
          break;
        default:
          if (isdigit(map[y][x])) {
            registry_.emplace<BoxType>(entity, BoxType::kMovable);
            registry_.emplace<Value>(entity, Value{map[y][x] - '0'});
            registry_.emplace<Renderable>(
                entity, Renderable{PURPLE, std::to_string(map[y][x] - '0'), true});
          } else if (islower(map[y][x])) {
            registry_.emplace<BoxType>(entity, BoxType::kTarget);
            registry_.emplace<Value>(entity, Value{map[y][x] - 'a' + 1});
            registry_.emplace<Target>(entity, Target{10, false});
            registry_.emplace<Renderable>(
                entity, Renderable{GREEN, std::to_string(map[y][x] - 'a' + 1), false});
          }
          break;
      }
    }
  }
}

void LevelManager::SetLevel(int index) {
  if (index >= 0 && index < levels_.size()) {
    current_level_ = index;
  } else {
    TraceLog(LOG_ERROR, "level index: %d is out of range!", index);
  }
}

void LevelManager::LoadLevel(int index) {
  SetLevel(index);
  LoadCurrentLevel();
}

void LevelManager::Next() {
  SetLevel(current_level_ + 1);
  LoadCurrentLevel();
}
void LevelManager::Prev() {
  SetLevel(current_level_ - 1);
  LoadCurrentLevel();
}
