#pragma once

/*
#include <utility>
#include "commponents/components.h"
#include "types.h"
class EventSystem {
public:
  EventSystem();
  virtual ~EventSystem();

  // [N]umber [T]o [O]perator
  void TriggerNTO(Entity number, Entity op, Vector2Int pos) {
    dispatcher_.trigger<NTOEvent>({number, op, pos});
  }

  template <typename T, typename Func>
  void Connect(Func&& func) {
    dispatcher_.sink<T>().connect(std::forward<Func>(func));
  }

private:
  entt::registry& registry_;
  entt::dispatcher dispatcher_;
};
*/
