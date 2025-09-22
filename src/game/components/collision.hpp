#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"
#include <vector>

struct BoundingBox {
    ecs::Coord coord_a_ {};
    ecs::Coord coord_b_ {};
};

struct ComponentCollision : ecs::Component<ComponentCollision> {
    explicit ComponentCollision (ecs::TypeInt id_entity)
    : Component(id_entity)
    {}    

    BoundingBox box;
    std::vector<BoundingBox> v_box_;
};