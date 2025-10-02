#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

struct SystemPhysics {
    void update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus) const noexcept;
};