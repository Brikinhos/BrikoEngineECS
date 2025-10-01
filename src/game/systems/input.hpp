#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

struct SystemInput {
    void update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus) const noexcept;
private:
    inline TypeInt fromBinaryToDecimal(bool up, bool down, bool left, bool right) const noexcept{
        return (up << 3) | (down << 2) | (left << 1) | (right);
    }
};