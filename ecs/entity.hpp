#pragma once

#include "aliases.hpp"

struct Entity {
    explicit Entity() = default;

    constexpr TypeInt getEntityID() const noexcept { return entityID; };

private:
       
    TypeInt entityID { nextID++ };
    inline static TypeInt nextID { 0 };
};
