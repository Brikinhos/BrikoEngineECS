#include "../../ecs/component.hpp"
#include "../../ecs/aliases.hpp"

struct ComponentPosition : ecs::Component<ComponentPosition> {
    explicit ComponentPosition (ecs::TypeInt id_entity)
        : Component(id_entity)
    {}
    
    std::size_t sizeOfComponentInBytes () override {
        return sizeof(*this);
    }
    
    ecs::TypeInt x {};
    ecs::TypeInt y {};
};