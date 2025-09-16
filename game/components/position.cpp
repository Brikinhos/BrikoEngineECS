#include "ecs/component.hpp"
#include "ecs/aliases.hpp"

struct ComponentPosition : Component<ComponentPosition> {
    explicit ComponentPosition (TypeInt id_entity)
        : Component(id_entity)
    {}
    
    std::size_t sizeOfComponentInBytes () override {
        return sizeof(*this);
    }
    
    std::uint64_t x {};
    std::uint64_t y {};
};