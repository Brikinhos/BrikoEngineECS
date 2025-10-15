#pragma once
#include "ecs/aliases.hpp"
#include "game/components/input.hpp"

struct EventButtonReleased {
    EventButtonReleased (ecs::TypeInt entity, GameInput input) 
    : entity_(entity), input_(input) {}
    ecs::TypeInt entity_;
    GameInput input_;
};