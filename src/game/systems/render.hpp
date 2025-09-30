#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"
#include "ecs/resourcemanager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

struct SystemRender {
    void update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus, sf::RenderWindow& window, ecs::ResourceManager& resource_manager) const noexcept;
};