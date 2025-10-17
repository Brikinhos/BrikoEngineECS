#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

struct SystemAnimation {
    void update (ecs::EntityManager& entitymanager, ecs::EventBus& eventbus);
};