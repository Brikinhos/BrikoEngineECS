#pragma once
#include "ecs/resourcemanager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

struct EventPrueba {
    ecs::TextureName name_;
    sf::Sprite sprite_;
};