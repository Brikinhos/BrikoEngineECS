#pragma once

#include "ecs/aliases.hpp"
#include "ecs/component.hpp"
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

struct ComponentFSM: ecs::Component<ComponentFSM> {
    explicit ComponentFSM (ecs::TypeInt id_entity)
        : Component (id_entity)
    {}    
    //ecs::TypeInt es en realidad std::size_t;
    using State = EntityState;
    using Transition = EventTransition;
    
    std::unordered_map<State, std::map<Transition, State>> m_FSM_;
    std::vector<EventTransition> v_transitions;

    State current_state_;
    State last_state_;
};