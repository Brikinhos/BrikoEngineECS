#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

struct ComponentSprite : ecs::Component<ComponentSprite> {
    explicit ComponentSprite (ecs::TypeInt id_entity)
    : Component(id_entity)
    {}    

    sf::Texture texture {};
    sf::Sprite sprite {texture};
};