#include "ecs/component.hpp"
#include "ecs/aliases.hpp"

struct ComponentLife : ecs::Component<ComponentLife> {
    explicit ComponentLife (ecs::TypeInt id_entity)
    : Component(id_entity)
    {}
    
    ecs::TypeInt l {};
};