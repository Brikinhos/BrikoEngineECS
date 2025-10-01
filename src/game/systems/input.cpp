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
            //Registra las entradas en el mapa de estados de las entradas
            auto& pair_button_state = cmp_input.m_input_state_[input.first];
            pair_button_state.first  = pair_button_state.second;
            pair_button_state.second = sf::Keyboard::isKeyPressed(input.second);
        }

        auto up_state    = cmp_input.m_input_state_.at(GameInput::UP);
        auto down_state  = cmp_input.m_input_state_.at(GameInput::DOWN);
        auto left_state  = cmp_input.m_input_state_.at(GameInput::LEFT);
        auto right_state = cmp_input.m_input_state_.at(GameInput::RIGHT);
        //Detecta que ha habido un cambio de estados entre todos los botones de dirección
        bool dir_changed = up_state.first    != up_state.second   || 
                           down_state.first  != down_state.second || 
                           left_state.first  != left_state.second || 
                           right_state.first != right_state.second;
        //Si ha habido un cambio de estado en los botones de dirección entonces se calcula la nueva dirección y
        // se añade al buffer, si la hay porque puede estar en un estado neutro, que en ese caso, no

        if (dir_changed) {
            auto id_input = fromBinaryToDecimal(up_state.second, down_state.second, left_state.second, right_state.second);
            auto dir = ComponentInput::truthtable_input_directions_.at(id_input);
            if (dir != GameInput::NOMOVE)
                cmp_input.buffer_input_.push_back(dir);
        }
        //Añade un botón que no es de dirección al buffer
        for (auto& inp : cmp_input.m_input_state_) {
            if (inp.first >= 4 ) {
                if (cmp_input.m_input_state_.at(inp.first).first != cmp_input.m_input_state_.at(inp.first).second && cmp_input.m_input_state_.at(inp.first).second) {
                    cmp_input.buffer_input_.push_back(inp.first);
                }
            }
        }
    }
}