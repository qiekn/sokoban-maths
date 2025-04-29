#include "input/input-handler.h"
#include <raylib.h>
#include <memory>
#include <utility>
#include <vector>
#include "components.h"
#include "constants.h"
#include "managers/maid.h"

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

// game programming design partterns: command
// https://gpp.tkchu.me/command.html
std::unique_ptr<Command> InputHandler::HandleInput() {
  float timer = GetTime();

  /* Player Movement */
  auto player_view = Maid::Instance().registry_.view<Player>();
  std::vector<Entity> player_entities(player_view->begin(), player_view->end());
  if (timer - last_move_time_ >= move_cooldown_) {
    int dx = 0, dy = 0;
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
      dx = -1;
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
      dx = 1;
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
      dy = -1;
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
      dy = 1;
    if (dx || dy) {
      last_move_time_ = timer;
      return std::make_unique<MoveCommand>(Maid::Instance().registry_, player_entities, dx, dy);
    }
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
