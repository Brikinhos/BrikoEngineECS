#pragma once
#include "ecs/aliases.hpp"

struct EventStateChanged {
    EventStateChanged (ecs::TypeInt entity ) 
    : entity_(entity) {}
    ecs::TypeInt entity_;
    
};