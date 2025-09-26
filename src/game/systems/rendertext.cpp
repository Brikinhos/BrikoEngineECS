#include "game/systems/rendertext.hpp"
#include "rendertext.hpp"
#include "game/components/textinfo.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

void SystemRenderText::update (ecs::EntityManager& entity_manager, sf::RenderWindow& window) const noexcept {
    
    auto& v_cmp_textinfo = entity_manager.getComponentVectorByType<ComponentTextInfo>();
    for (auto& cmp_textinfo : v_cmp_textinfo) {
        auto* cmp_input = entity_manager.getComponentFromEntityID<ComponentInput>(cmp_textinfo.getEntityID());
        if (cmp_input) {
            cmp_textinfo.text_.setString(getSSComponentInput(*cmp_input).str());
            auto& text = cmp_textinfo.text_;
            window.draw(text);
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
