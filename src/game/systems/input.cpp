#include "game/systems/input.hpp"
#include "ecs/entitymanager.hpp"
#include "game/components/input.hpp"
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>


void SystemInput::update (ecs::EntityManager& entity_manager) const noexcept {
    auto& v_input_component = entity_manager.getComponentVectorByType<ComponentInput>();
    for (auto& cmp_input : v_input_component) {
        for (auto input: cmp_input.m_bind_keyboard_) {
            cmp_input.m_input_state_[input.first] = sf::Keyboard::isKeyPressed(input.second);
        }
    }
}