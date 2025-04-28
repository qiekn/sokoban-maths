#pragma once

#include "systems/render-system.h"

class WinConditionSystem {
public:
  explicit WinConditionSystem(entt::registry& registry) : registry_(registry) {}

  bool IsLevelComplete() const;

private:
  entt::registry& registry_;
};
