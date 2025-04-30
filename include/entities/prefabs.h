#pragma once

#include "commponents/components.h"
#include "types.h"
class Prefabs {
public:
  Prefabs(Registry& registry);
  virtual ~Prefabs();

  void CreatePlayer(Position pos);
  void CreateBox(Position pos);
  void CreateWall(Position pos);
  void CreateFloor(Position pos);
  void CraeteNumber(Position pos, int val);
  void CreateOperator(Position pos);
  void CreateTarget(Position pos, int val);

  void CreateOperatorAdd(Position pos);
  void CreateOperatorSub(Position pos);
  void CreateOperatorMul(Position pos);
  void CreateOperatorDiv(Position pos);

private:
  Registry& registry_;
};
