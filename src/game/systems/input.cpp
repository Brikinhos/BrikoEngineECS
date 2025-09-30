#include "game/systems/input.hpp"
#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"
#include "ecs/resourcemanager.hpp"
#include "game/components/input.hpp"
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "game/events/prueba.hpp"


void SystemInput::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus) const noexcept {
    auto& v_input_component = entity_manager.getComponentVectorByType<ComponentInput>();
    for (auto& cmp_input : v_input_component) {
        for (auto input: cmp_input.m_bind_keyboard_) {
            cmp_input.m_input_state_[input.first] = sf::Keyboard::isKeyPressed(input.second);
            if (sf::Keyboard::isKeyPressed(input.second)) {
                EventPrueba event_prueba;
                event_prueba.name = ecs::TextureName::Prueba;
                eventbus.emit(event_prueba);
            }
        }
    }
}