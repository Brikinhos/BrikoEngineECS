#pragma once
#include "ecs/aliases.hpp"
#include "ecs/entity.hpp"
#include "ecs/resourcemanager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

struct EventButtonPressed {
    EventButtonPressed (ecs::TypeInt entity ) 
    : entity_(entity) {}
    ecs::TypeInt entity_;
};