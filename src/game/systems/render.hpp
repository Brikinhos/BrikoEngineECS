#pragma once

#include "ecs/entitymanager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

struct SystemRender {
    void update (ecs::EntityManager& entity_manager, sf::RenderWindow& window) const noexcept;
};