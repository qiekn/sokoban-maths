#pragma once

#include "types.h"
struct NumberToOperatorEvent {
  Entity num_entity;
  Entity op_entity;
  Vector2Int direction;
};
