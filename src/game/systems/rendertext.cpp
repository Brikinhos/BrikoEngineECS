#include "game/systems/rendertext.hpp"
#include "datastructs/slotmap.hpp"
#include "ecs/eventhandler.hpp"
#include "game/components/input.hpp"
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
    << cmp_input.m_input_state_[GameInput::UPLEFT].second     << " " << cmp_input.m_input_state_[GameInput::UP].second << " " << cmp_input.m_input_state_[GameInput::UPRIGHT].second << "\n"
    << cmp_input.m_input_state_[GameInput::LEFT].second       << "   " << cmp_input.m_input_state_[GameInput::RIGHT].second << "\n"
    << cmp_input.m_input_state_[GameInput::DOWNLEFT].second   << " " << cmp_input.m_input_state_[GameInput::DOWN].second << " " << cmp_input.m_input_state_[GameInput::DOWNRIGHT].second << "\n"
    << "ACTION  STATE" << "\n" 
    << "ATTACK    " << cmp_input.m_input_state_[GameInput::ATTACK].second    << "\n"
    << "JUMP      " << cmp_input.m_input_state_[GameInput::JUMP].second      << "\n"
    << "USE       " << cmp_input.m_input_state_[GameInput::USE].second       << "\n"
    << "SELECT    " << cmp_input.m_input_state_[GameInput::SELECT].second    << "\n"
    << "START     " << cmp_input.m_input_state_[GameInput::START].second     << "\n";

    //buffer_input_
    ss
    << "CIRCULAR BUFFER: ";
    for (auto& input : cmp_input.buffer_input_.getOrderedBuffer()) {
        ss << cmp_input.m_input_string[input] << " ";
    }
   
    return ss;
}