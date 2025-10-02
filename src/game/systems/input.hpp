#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"
#include "game/components/input.hpp"

struct SystemInput {
    void update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus) const noexcept;
private:
    inline GameInput fromFourDirToEightDir(std::array<bool, 4> v_dir_states) const noexcept{
        int i = (v_dir_states.at(0) << 3) | (v_dir_states.at(1) << 2) | (v_dir_states.at(2) << 1) | (v_dir_states.at(3));
        return ComponentInput::truthtable_input_directions_.at(i);
    }
};