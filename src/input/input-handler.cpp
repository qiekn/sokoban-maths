#include "input/input-handler.h"
#include <raylib.h>
#include <memory>
#include <utility>
#include <vector>
#include "components.h"
#include "constants.h"

InputHandler::InputHandler(Registry& registry) : registry_(registry) {}

InputHandler::~InputHandler() {}

// game programming design partterns: command
// https://gpp.tkchu.me/command.html
std::unique_ptr<Command> InputHandler::HandleInput() {
  /* Player Movement */
  auto player_view = registry_.view<Player>();
  std::vector<Entity> player_entities(player_view->begin(), player_view->end());

  if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
    return std::make_unique<MoveCommand>(registry_, player_entities, -1, 0);
  }

  if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
    return std::make_unique<MoveCommand>(registry_, player_entities, 1, 0);
  }

  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
    return std::make_unique<MoveCommand>(registry_, player_entities, 0, -1);
  }

  if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
    return std::make_unique<MoveCommand>(registry_, player_entities, 0, 1);
  }

  /* Player Functions */
  if (IsKeyPressed(KEY_Z)) {
    if (!history_.empty()) {
      auto cmd = std::move(history_.back());
      history_.pop_back();
      cmd->Undo();
    }
    return std::make_unique<EmptyCommand>();
  }

  if (IsKeyPressed(KEY_R)) {
    // todo
  }

  if (IsKeyPressed(KEY_SPACE)) {
    TraceLog(LOG_WARNING, "Space pressed");
  }

  return nullptr;
}

void InputHandler::Update() {
  auto cmd = std::move(HandleInput());
  if (cmd == nullptr) return;
  if (!cmd->IsEmpty()) {
    while (history_.size() >= kMaxUndoHistry) {
      history_.pop_front();
    }
    cmd->Execute();
    history_.emplace_back(std::move(cmd));
  }
}
