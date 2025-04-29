#pragma once

#include <optional>
#include "types.h"

/**
 * @class Maid
 * @brief 有什么事情尽管来问女仆小姐姐就好了
 *
 */
class Maid {
public:
  /* singleton */
  static Maid& Instance() {
    static Maid instance;
    return instance;
  }

  /* data */
  Map entity_map_;
  Registry registry_;

  /* method */
  void Register(Entity entity);
  void Unregister(Entity entity);
  Entity GetEntity(int x, int y);
  Entity GetEntity(Vector2Int pos);

  template <typename T>
  std::optional<T> GetComponent(int x, int y);

  template <typename T>
  std::optional<T> GetComponent(Vector2Int pos);

private:
  Maid();

  size_t rows_;
  size_t cols_;
};
