#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"

struct ComponentVelocity : ecs::Component<ComponentVelocity> {
    explicit ComponentVelocity (ecs::TypeInt id_entity)
        : Component(id_entity)
    {}
    
    ecs::TypeInt velocity {};
};