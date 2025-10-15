#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

struct SystemFSM {
    void update (ecs::EntityManager& entitymanager, ecs::EventBus& eventbus_input);
    void init(ecs::EntityManager& entitymanager, ecs::EventBus& eventbus_input);
};