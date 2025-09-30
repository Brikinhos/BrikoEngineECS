#pragma once

#include "ecs/aliases.hpp"
#include "ecs/component.hpp"

enum class State {
    IDLE,
    MOVE,
    JUMP,
    ATTACK
};

struct ComponentFSM: ecs::Component<ComponentFSM> {
    explicit ComponentFSM (ecs::TypeInt id_entity)
        : Component (id_entity)
    {}    
};