#include "game/systems/rendertext.hpp"
#include "game/components/input.hpp"
#include "rendertext.hpp"
#include "game/components/textinfo.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <sstream>

void SystemRenderText::update (ecs::EntityManager& entity_manager, sf::RenderWindow& window) const noexcept {
    
    std::cout << "HOLA";
    auto& v_cmp_textinfo = entity_manager.getComponentVectorByType<ComponentTextInfo>();
    std::cout << "HOLA2";
    for (auto& cmp_textinfo : v_cmp_textinfo) {
        std::cout << "HOLA3";
        auto* cmp_input = entity_manager.getComponentFromEntityID<ComponentInput>(cmp_textinfo.getEntityID());
        if (cmp_input) {
            std::cout << "HOLA4";
            //cmp_textinfo.text.setString(getSSComponentInput(*cmp_input).str());
            cmp_textinfo.text.setString("TEXT");
            std::cout << "HOLA5";
            auto& text = cmp_textinfo.text;
            window.draw(text);
            std::cout << "HOLA6";
        }
        
    }
}

std::stringstream SystemRenderText::getSSComponentInput(ComponentInput &cmp_input) const{

    std::stringstream ss;
    
    ss << "ACTION\tSTATE" 
    << "UP\t"     << cmp_input.m_input_state_[GameInput::UP]
    << "DOWN\t"   << cmp_input.m_input_state_[GameInput::DOWN] 
    << "LEFT\t"   << cmp_input.m_input_state_[GameInput::LEFT]
    << "RIGHT\t"  << cmp_input.m_input_state_[GameInput::RIGHT]
    << "ATTACK\t" << cmp_input.m_input_state_[GameInput::ATTACK]
    << "JUMP\t"   << cmp_input.m_input_state_[GameInput::JUMP]
    << "USE\t"    << cmp_input.m_input_state_[GameInput::USE]
    << "SELECT\t" << cmp_input.m_input_state_[GameInput::SELECT]
    << "START\t"  << cmp_input.m_input_state_[GameInput::START];

    return ss;
}
