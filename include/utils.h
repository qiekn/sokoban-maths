#pragma once

#include <raylib.h>
#include "types.h"

Color Haxc(const std::string& color);

Vector2Int GridToWorld(int x, int y);

Vector2Int GridToWorld(Vector2Int pos);

// inline Vector2Int WorldToGrid()
