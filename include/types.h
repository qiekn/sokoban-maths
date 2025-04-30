#pragma once

#include "entt.h"

struct Vector2Int {
  int x, y;

  Vector2Int() : x(0), y(0) {}

  Vector2Int(int _x, int _y) : x(_x), y(_y) {}

  Vector2Int operator+(const Vector2Int& rhs) const { return Vector2Int(x + rhs.x, y + rhs.y); }

  Vector2Int operator-(const Vector2Int& rhs) const { return Vector2Int(x - rhs.x, y - rhs.y); }

  Vector2Int operator*(int rhs) const { return Vector2Int(x * rhs, y * rhs); }

  Vector2Int operator/(int rhs) const { return Vector2Int(x / rhs, y / rhs); }

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

using Map = std::unordered_map<Vector2Int, Entity>;
