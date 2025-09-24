#pragma once

#include "ecs/entitymanager.hpp"

struct SystemInput {
    void update (ecs::EntityManager& entity_manager) const noexcept;
};