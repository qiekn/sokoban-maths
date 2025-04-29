#pragma once

#include <vector>
#include "entt.h"
#include "types.h"

class Command {
public:
  virtual ~Command() {}
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  bool IsEmpty();

protected:
  bool is_empty_command_ = false;
};

class MoveCommand : public Command {
public:
  MoveCommand(Registry& registry, const std::vector<Entity>& entities, int dx, int dy)
      : registry_(registry), entities_(entities), dx_(dx), dy_(dy) {}

  MoveCommand(Registry& registry, Entity entity, int dx, int dy)
      : registry_(registry), dx_(dx), dy_(dy) {
    entities_.push_back(entity);
  }

  virtual void Execute() override;
  virtual void Undo() override;

private:
  Registry& registry_;
  std::vector<Entity> entities_;
  int dx_;
  int dy_;
};

class EmptyCommand : public Command {
public:
  EmptyCommand() { is_empty_command_ = true; }
  void Execute() override { return; }
  void Undo() override { return; }
};
