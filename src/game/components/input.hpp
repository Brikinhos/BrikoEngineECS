#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"

struct ComponentInput : ecs::Component<ComponentInput> {
    explicit ComponentInput (ecs::TypeInt id_entity)
    : Component(id_entity)
    {}
    
    ecs::TypeInt l {};
};