#pragma once

#include "ecs/entitymanager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include "game/components/input.hpp"

struct SystemRenderText {
    void update (ecs::EntityManager& entity_manager, sf::RenderWindow& window) const noexcept;
private:
    std::stringstream getSSComponentInput (ComponentInput& cmp_input) const;
};