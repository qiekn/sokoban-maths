#include "commands.h"
#include <raylib.h>
#include <string>
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

void MathOperatorCommand::Execute() {
  TraceLog(LOG_DEBUG, "MathOperatorCommand: Execute");
  // disable number rendering
  registry_.emplace<Disable>(num_entity_);
  // update operator box value
  auto& num = registry_.get<Number>(num_entity_);
  auto& op = registry_.get<MathOperator>(op_entitty_);
  old_value_ = op.value;
  op.value = op.calculate(op.value, num.value);
  // change operator rendering style
  auto& render = registry_.get<SpriteRenderer>(op_entitty_);
  old_type_ = render.type;
  render.text = std::to_string(op.value);
  render.type = SpriteType::kText;
}

void MathOperatorCommand::Undo() {
  TraceLog(LOG_DEBUG, "MathOperatorCommand: Undo");
  // enable number rendering
  registry_.remove<Disable>(num_entity_);
  // recover operator box value
  auto& op = registry_.get<MathOperator>(op_entitty_);
  auto& render = registry_.get<SpriteRenderer>(op_entitty_);
  op.value = old_value_;
  render.text = std::to_string(op.value);
  render.type = old_type_;
}
