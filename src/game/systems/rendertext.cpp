#include "game/systems/rendertext.hpp"
#include "datastructs/slotmap.hpp"
#include "ecs/eventhandler.hpp"
#include "rendertext.hpp"
#include "game/components/textinfo.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>

void SystemRenderText::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus, sf::RenderWindow& window) const noexcept {
    
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
    //m_input_state_
    ss 
    << "ACTION  BEFORE  AFTER" << "\n" 
    << "UP        " << cmp_input.m_input_state_[GameInput::UP].first     << "       " << cmp_input.m_input_state_[GameInput::UP].second     << "\n"
    << "DOWN      " << cmp_input.m_input_state_[GameInput::DOWN].first   << "       " << cmp_input.m_input_state_[GameInput::DOWN].second   << "\n"
    << "LEFT      " << cmp_input.m_input_state_[GameInput::LEFT].first   << "       " << cmp_input.m_input_state_[GameInput::LEFT].second   << "\n"
    << "RIGHT     " << cmp_input.m_input_state_[GameInput::RIGHT].first  << "       " << cmp_input.m_input_state_[GameInput::RIGHT].second  << "\n"
    << "ATTACK    " << cmp_input.m_input_state_[GameInput::ATTACK].first << "       " << cmp_input.m_input_state_[GameInput::ATTACK].second << "\n"
    << "JUMP      " << cmp_input.m_input_state_[GameInput::JUMP].first   << "       " << cmp_input.m_input_state_[GameInput::JUMP].second   << "\n"
    << "USE       " << cmp_input.m_input_state_[GameInput::USE].first    << "       " << cmp_input.m_input_state_[GameInput::USE].second    << "\n"
    << "SELECT    " << cmp_input.m_input_state_[GameInput::SELECT].first << "       " << cmp_input.m_input_state_[GameInput::SELECT].second << "\n"
    << "START     " << cmp_input.m_input_state_[GameInput::START].first  << "       " << cmp_input.m_input_state_[GameInput::START].second  << "\n";

    //buffer_input_

    ss
    << "CIRCULAR BUFFER: " << cmp_input.buffer_input_.getStringBufer().str();
   
    return ss;
}