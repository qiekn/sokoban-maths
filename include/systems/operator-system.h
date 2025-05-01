#pragma once

#include <entt.h>
#include <raylib.h>
#include "commands.h"
#include "events.h"
#include "managers/command-manager.h"

class OperatorSystem {
public:
  OperatorSystem(entt::registry& registry, entt::dispatcher& dispatcher,
                 CommandManager& command_manager)
      : registry_(registry),
        dispatcher_(dispatcher),
        command_manager_(command_manager) {
    dispatcher_.sink<NumberToOperatorEvent>().connect<&OperatorSystem::Handle>(
        *this);
  }

  void Handle(const NumberToOperatorEvent& event) {
    TraceLog(LOG_DEBUG, "OperatorSystem: Handler");
    auto cmd = std::make_unique<MathOperatorCommand>(
        registry_, dispatcher_, event.num_entity, event.op_entity);
    command_manager_.Execute(std::move(cmd));
  }

private:
  entt::registry& registry_;
  entt::dispatcher& dispatcher_;
  CommandManager& command_manager_;
};
