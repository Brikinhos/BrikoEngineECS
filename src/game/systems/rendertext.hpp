#pragma once

#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>
#include "game/components/FSM.hpp"
#include "game/components/input.hpp"

struct SystemRenderText {
    void update (ecs::EntityManager& entity_manager, ecs::EventBus& evenbus, sf::RenderWindow& window) const noexcept;
private:
    std::stringstream getSSComponentInput (ComponentInput& cmp_input) const;
    std::stringstream getSSComponentFSM (ComponentFSM& cmp_FSM) const;
};