#include "commands.h"
#include <raylib.h>
#include "commponents/components.h"

bool Command::IsEmpty() { return is_empty_command_; }

void DirectMoveCommand::Execute() {
  for (auto entity : entities_) {
    auto& pos = registry_.get<Position>(entity);
    pos.x += dx_;
    pos.y += dy_;
  }
}

void DirectMoveCommand::Undo() {
  for (auto entity : entities_) {
    auto& pos = registry_.get<Position>(entity);
    pos.x -= dx_;
    pos.y -= dy_;
  }
}

void ChainMoveCommand::Execute() {
  for (auto [entity, dir] : to_move_) {
    auto& pos = registry_.get<Position>(entity);
    pos += dir;
  }
}

void ChainMoveCommand::Undo() {
  for (auto [entity, dir] : to_move_) {
    auto& pos = registry_.get<Position>(entity);
    pos -= dir;
  }
}

// TODO:  <2025-04-30 21:48, @qiekn> //
void ResetCommand::Execute() {}
void ResetCommand::Undo() {}
