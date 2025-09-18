#include "ecs/component.hpp"
#include "/ecs/aliases.hpp"

struct ComponentLife : ecs::Component<ComponentLife> {
    explicit ComponentLife (ecs::TypeInt id_entity)
    : Component(id_entity)
    {}
    
    std::size_t sizeOfComponentInBytes () override {
        return sizeof(*this);
    }
    
    ecs::TypeInt l {};
};