#pragma once

#include "aliases.hpp"

enum class TypeEntity {
    PLAYER,
    ENEMY
};

namespace ecs {

    struct Entity {
        explicit Entity(TypeEntity type_entity) :
            type_entity_(type_entity) {}
        
        constexpr TypeInt getEntityID() const noexcept { return entityID; };

        TypeEntity type_entity_;
        
    private:
        
        TypeInt entityID { nextID++ };
        inline static TypeInt nextID { 0 };
    };
}
