#pragma once

#include "ecs/entitymanager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include <string>
#include "game/components/input.hpp"
#include <string>

struct SystemRenderText {
    void update (ecs::EntityManager& entity_manager, sf::RenderWindow& window) const noexcept;
private:
    std::stringstream getSSComponentInput (ComponentInput& cmp_input) const;
};