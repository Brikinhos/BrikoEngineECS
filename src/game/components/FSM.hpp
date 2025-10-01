#pragma once

#include "ecs/aliases.hpp"
#include "ecs/component.hpp"
#include <string>
#include <unordered_map>
#include <map>

struct ComponentFSM: ecs::Component<ComponentFSM> {
    explicit ComponentFSM (ecs::TypeInt id_entity)
        : Component (id_entity)
    {}    
    //ecs::TypeInt es en realidad std::size_t;
    using State = std::string;
    using StateID = ecs::TypeInt;
    using Transition = std::string;
    using TransitionID = ecs::TypeInt;

    std::unordered_map<StateID,      State>      m_states_;
    std::unordered_map<TransitionID, Transition> m_transitions_;
    std::unordered_map<StateID, std::map<TransitionID, StateID>> m_FSM_;

    StateID current_state_;
};