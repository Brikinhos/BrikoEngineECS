#include "game/systems/input.hpp"
#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"
#include "game/components/input.hpp"
#include "game/events/buttonpressed.hpp"
#include "game/events/buttonreleased.hpp"
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>

void SystemInput::update (ecs::EntityManager& entity_manager, ecs::EventBus& event_bus_input) const noexcept {
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
            input_state.second.at(0) = input_state.second.at(1);
            if (input_state.first > GameInput::DOWNRIGHT)
                input_state.second.at(1) = sf::Keyboard::isKeyPressed(cmp_input.m_bind_keyboard_.at(input_state.first));
            else 
                input_state.second.at(1) = (input_state.first == calculated_dir);
        }

        auto isButtonPressed = [&m_input_state](GameInput input){
            return input != GameInput::NOMOVE && (m_input_state.at(input).at(0) == false && m_input_state.at(input).at(1) == true);
        };
        
        auto isButtonReleased = [&m_input_state](GameInput input){
            return input != GameInput::NOMOVE && (m_input_state.at(input).at(0) == true && m_input_state.at(input).at(1) == false);
        };

        //Registra si los botones han sido presionados por primera vez o soltados en este frame
        //Ya de paso esas nuevas pulsaciones las introducimos en el buffer circular

        for (auto& input_state : m_input_state) {
            if (isButtonPressed(input_state.first)) {
                m_input_state.at(input_state.first).at(2) = true; 
                m_input_state.at(input_state.first).at(3) = false; 
                cmp_input.buffer_input_.push_back(input_state.first);
            } else if (isButtonReleased(input_state.first)) {
                m_input_state.at(input_state.first).at(2) = false;
                m_input_state.at(input_state.first).at(3) = true;
            } else {
                m_input_state.at(input_state.first).at(2) = false;
                m_input_state.at(input_state.first).at(3) = false;
            }
        }

        //Emitimos eventos por las pulsaciones
        for (auto& input_state : m_input_state) {
            if (input_state.second.at(0) == true && input_state.second.at(1) == false) {
                event_bus_input.emit(EventButtonReleased(cmp_input.getEntityID(), input_state.first));
                std::cout << "emit event release button\n";
            }
        }
        for (auto& input_state : m_input_state) {
            if (input_state.second.at(0) == false && input_state.second.at(1) == true) {
                event_bus_input.emit(EventButtonPressed(cmp_input.getEntityID(), input_state.first));
                std::cout << "emit event push button\n";
            }
        }
    }
}