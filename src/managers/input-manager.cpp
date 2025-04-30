#include "managers/input-manager.h"
#include <raylib.h>
#include <memory>
#include <utility>
#include <vector>
#include "commponents/components.h"
#include "constants.h"
#include "maid.h"
#include "systems/move-system.h"
#include "types.h"

InputManager::InputManager(Registry& registry) : registry_(registry) {}

InputManager::~InputManager() {}

// game programming design partterns: command
// https://gpp.tkchu.me/command.html
std::unique_ptr<Command> InputManager::HandleInput() {
  // player Movement
  {
    // get player entities
    auto player_view = registry_.view<Player>();
    std::vector<Entity> players(player_view->begin(), player_view->end());
    // get move dir
    Vector2Int dir = GetMoveInput();
    if (dir.x || dir.y) {
      // can I move?
      MoveBuffer to_move = Maid::Instance().move_system_.Move(players, dir);
      return std::make_unique<ChainMoveCommand>(registry_, to_move);
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

void InputManager::Update() {
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

Vector2Int InputManager::GetMoveInput() {
  float timer = GetTime();
  int dx = 0, dy = 0;
  if (timer - last_move_time_ >= move_cooldown_) {
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
    }
  }
  return Vector2Int{dx, dy};
}
