#include "game/systems/input.hpp"
#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"
#include "game/components/input.hpp"
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>

void SystemInput::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus) const noexcept {
    auto& v_input_component = entity_manager.getComponentVectorByType<ComponentInput>();
    for (auto& cmp_input : v_input_component) {
        //Registra el estado actual de la entrada
        std::array<bool, 4> dir_states;
        for (auto input: cmp_input.m_bind_keyboard_) {
            //Registra el estado de las pulsaciones de los botones físicos
            if (input.first >= GameInput::UP && input.first <= GameInput::RIGHT) {
                dir_states.at(input.first) = sf::Keyboard::isKeyPressed(input.second);
            } else if (input.first > GameInput::RIGHT) {
                cmp_input.m_input_state_.at(input.first).first = cmp_input.m_input_state_.at(input.first).second;
                cmp_input.m_input_state_.at(input.first).second = sf::Keyboard::isKeyPressed(input.second);
            }
        }

        GameInput calculated_dir = fromFourDirToEightDir(dir_states);
        for (int i = GameInput::UP; i <= GameInput::DOWNRIGHT; ++i) {
            cmp_input.m_input_state_.at(static_cast<GameInput>(i)).first = cmp_input.m_input_state_.at(static_cast<GameInput>(i)).second;
            cmp_input.m_input_state_.at(static_cast<GameInput>(i)).second = false;
        }
        if (calculated_dir != GameInput::NOMOVE) {
            cmp_input.m_input_state_.at(calculated_dir).second = true;
        }
        //Registra las entradas en el buffer
        //Primero la dirección
        if (calculated_dir != GameInput::NOMOVE && (cmp_input.m_input_state_.at(calculated_dir).first != cmp_input.m_input_state_.at(calculated_dir).second) && cmp_input.m_input_state_.at(calculated_dir).second) {
            cmp_input.buffer_input_.push_back(calculated_dir);
        }
        //Ahora las otras entradas
        for (std::size_t i = GameInput::DOWNRIGHT + 1; i < cmp_input.m_input_state_.size(); ++i) {
            if (cmp_input.m_input_state_.at(static_cast<GameInput>(i)).first != cmp_input.m_input_state_.at(static_cast<GameInput>(i)).second && cmp_input.m_input_state_.at(static_cast<GameInput>(i)).second) {
                cmp_input.buffer_input_.push_back(static_cast<GameInput>(i));
            }
        }
    }
}