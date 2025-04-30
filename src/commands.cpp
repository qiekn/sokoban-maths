#include "commands.h"
#include "commponents/components.h"

bool Command::IsEmpty() { return is_empty_command_; }

void MoveCommand::Execute() {
  for (auto entity : entities_) {
    auto& pos = registry_.get<Position>(entity);
    pos.x += dx_;
    pos.y += dy_;
  }
}

void MoveCommand::Undo() {
  for (auto entity : entities_) {
    auto& pos = registry_.get<Position>(entity);
    pos.x -= dx_;
    pos.y -= dy_;
  }
}
