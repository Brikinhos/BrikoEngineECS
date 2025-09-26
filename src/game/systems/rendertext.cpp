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
    
    ss 
    << "ACTION  STATE" << "\n" 
    << "UP        " << cmp_input.m_input_state_[GameInput::UP]     << "\n"
    << "DOWN      " << cmp_input.m_input_state_[GameInput::DOWN]   << "\n"
    << "LEFT      " << cmp_input.m_input_state_[GameInput::LEFT]   << "\n"
    << "RIGHT     " << cmp_input.m_input_state_[GameInput::RIGHT]  << "\n"
    << "ATTACK    " << cmp_input.m_input_state_[GameInput::ATTACK] << "\n"
    << "JUMP      " << cmp_input.m_input_state_[GameInput::JUMP]   << "\n"
    << "USE       " << cmp_input.m_input_state_[GameInput::USE]    << "\n"
    << "SELECT    " << cmp_input.m_input_state_[GameInput::SELECT] << "\n"
    << "START     " << cmp_input.m_input_state_[GameInput::START]  << "\n";

    return ss;
}
