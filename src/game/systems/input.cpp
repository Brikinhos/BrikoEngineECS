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
        //Calculamos la dirección en 8 posibles en función de las 4 del teclado o mando
        std::array<bool, 4> dir_states;
        dir_states.at(GameInput::UP)    = sf::Keyboard::isKeyPressed(cmp_input.m_bind_keyboard_.at(GameInput::UP));
        dir_states.at(GameInput::DOWN)  = sf::Keyboard::isKeyPressed(cmp_input.m_bind_keyboard_.at(GameInput::DOWN));
        dir_states.at(GameInput::LEFT)  = sf::Keyboard::isKeyPressed(cmp_input.m_bind_keyboard_.at(GameInput::LEFT));
        dir_states.at(GameInput::RIGHT) = sf::Keyboard::isKeyPressed(cmp_input.m_bind_keyboard_.at(GameInput::RIGHT));
        
        GameInput calculated_dir = fromFourDirToEightDir(dir_states);
        
        //Registra el estado actual de la entrada
        auto& m_input_state = cmp_input.m_input_state_;
        for (auto& input_state : m_input_state) {
            input_state.second.first  = input_state.second.second;
            if (input_state.first > GameInput::DOWNRIGHT)
                input_state.second.second = sf::Keyboard::isKeyPressed(cmp_input.m_bind_keyboard_.at(input_state.first));
            else 
                input_state.second.second = input_state.first == calculated_dir;
        }

        //Registra las entradas en el buffer
        //Primero la dirección
        if (calculated_dir != GameInput::NOMOVE && (m_input_state.at(calculated_dir).first != m_input_state.at(calculated_dir).second) && m_input_state.at(calculated_dir).second) {
            cmp_input.buffer_input_.push_back(calculated_dir);
        }
        //Ahora las otras entradas
        for (std::size_t i = GameInput::DOWNRIGHT + 1; i < m_input_state.size(); ++i) {
            if (m_input_state.at(static_cast<GameInput>(i)).first != m_input_state.at(static_cast<GameInput>(i)).second && m_input_state.at(static_cast<GameInput>(i)).second) {
                cmp_input.buffer_input_.push_back(static_cast<GameInput>(i));
            }
        }
    }
}