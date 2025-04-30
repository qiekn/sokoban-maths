#pragma once

#include "entities/prefabs.h"
#include "managers/input-manager.h"
#include "managers/level-manager.h"
#include "systems/move-system.h"
#include "systems/render-system.h"
#include "types.h"

/**
 * @class Maid
 * @brief 有什么事情尽管来问女仆小姐姐就好了
 */
class Maid {
public:
  /* singleton */
  static Maid& Instance() {
    static Maid instance;
    return instance;
  }

  /* entities */
  Registry registry_;
  Prefabs prefabs_;
  Map entity_map_;

  /* managers */
  LevelManager level_manager_;
  InputManager input_system_;

  /* systems */
  MoveSystem move_system_;
  RenderSystem render_system_;

private:
  /* C++ 的成员初始化顺序严格遵循类中成员声明的顺序 */
  Maid()
      : registry_(),
        prefabs_(registry_),
        entity_map_(),
        level_manager_(registry_, prefabs_),
        input_system_(registry_),
        move_system_(registry_),
        render_system_() {}
};
