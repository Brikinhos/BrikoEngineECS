#include "ecs/component.hpp"
#include "ecs/aliases.hpp"

struct ComponentVelocity : ecs::Component<ComponentVelocity> {
    explicit ComponentVelocity (ecs::TypeInt id_entity)
        : Component(id_entity)
    {}
    
    std::size_t sizeOfComponentInBytes () override {
        return sizeof(*this);
    }
    
    ecs::TypeInt v {};
};