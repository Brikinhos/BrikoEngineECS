#pragma once

#include "ecs/aliases.hpp"
#include "ecs/component.hpp"
#include <cstdint>
#include <unordered_map>
#include <map>

struct FSM {
    using State = std::uint8_t;
    using Transition = EventTransition;
    std::unordered_map<State, std::map<Transition, State>> m_FSM_;
    State current_state_;
    State last_state_;
};

struct ComponentFSM: ecs::Component<ComponentFSM> {
    explicit ComponentFSM (ecs::TypeInt id_entity)
        : Component (id_entity)
    {}        
    std::unordered_map<TypeFSM, FSM> mm_FSM_;
};