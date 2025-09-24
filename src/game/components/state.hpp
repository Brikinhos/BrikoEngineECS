#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"
#include "ecs/entity.hpp"
#include <vector>

struct ComponentState : ecs::Component<ComponentState> {
    explicit ComponentState (ecs::TypeInt id_entity)
        : Component(id_entity)
    {}    

};