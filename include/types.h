#pragma once

#include "entt.h"

struct Vector2Int {
  int x = 0;
  int y = 0;

  Vector2Int() = default;

  Vector2Int(int _x, int _y) : x(_x), y(_y) {}

  Vector2Int operator+(const Vector2Int& rhs) const {
    return Vector2Int(x + rhs.x, y + rhs.y);
  }

  Vector2Int operator-(const Vector2Int& rhs) const {
    return Vector2Int(x - rhs.x, y - rhs.y);
  }

  Vector2Int operator*(int rhs) const { return Vector2Int(x * rhs, y * rhs); }

  Vector2Int operator/(int rhs) const { return Vector2Int(x / rhs, y / rhs); }

  bool operator==(const Vector2Int& rhs) const {
    return x == rhs.x && y == rhs.y;
  }

  Vector2Int& operator+=(const Vector2Int& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  Vector2Int& operator-=(const Vector2Int& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
};

using Registry = entt::registry;
using Entity = entt::entity;

// specialize std::hash for Vector2Int
namespace std {
template <>
struct hash<Vector2Int> {
  std::size_t operator()(const Vector2Int& v) const {
    return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
  }
};
}  // namespace std

using Map = std::unordered_map<Vector2Int, Entity, std::hash<Vector2Int>>;
