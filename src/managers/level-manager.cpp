#include "managers/level-manager.h"

void LevelManager::LoadJson() {}

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
