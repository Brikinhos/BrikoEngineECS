#include "game/systems/rendertext.hpp"
#include "ecs/eventhandler.hpp"
#include "game/components/FSM.hpp"
#include "game/components/input.hpp"
#include "rendertext.hpp"
#include "game/components/textinfo.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include "ecs/aliases.hpp"

void SystemRenderText::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus, sf::RenderWindow& window) const noexcept {
    
    auto& v_cmp_textinfo = entity_manager.getComponentVectorByType<ComponentTextInfo>();
    for (auto& cmp_textinfo : v_cmp_textinfo) {
        std::stringstream ss;
        //INPUT
        auto* cmp_input = entity_manager.getComponentFromEntityID<ComponentInput>(cmp_textinfo.getEntityID());
        if (cmp_input) {
            ss << getSSComponentInput(*cmp_input).str();
        }
        //FSM
        auto* cmp_FSM = entity_manager.getComponentFromEntityID<ComponentFSM>(cmp_textinfo.getEntityID());
        if (cmp_FSM) {
            ss << getSSComponentFSM(*cmp_FSM).str();
        }
        cmp_textinfo.text_.setString(ss.str());
        auto& text = cmp_textinfo.text_;
        window.draw(text);
    }
}

std::stringstream SystemRenderText::getSSComponentInput(ComponentInput &cmp_input) const{
    std::stringstream ss;
    //m_input_state_
    ss 
    << cmp_input.m_input_state_[GameInput::UPLEFT].at(1)     << " " << cmp_input.m_input_state_[GameInput::UP].at(1) << " " << cmp_input.m_input_state_[GameInput::UPRIGHT].at(1) << "\n"
    << cmp_input.m_input_state_[GameInput::LEFT].at(1)       << "   " << cmp_input.m_input_state_[GameInput::RIGHT].at(1) << "\n"
    << cmp_input.m_input_state_[GameInput::DOWNLEFT].at(1)   << " " << cmp_input.m_input_state_[GameInput::DOWN].at(1) << " " << cmp_input.m_input_state_[GameInput::DOWNRIGHT].at(1) << "\n"
    << "ACTION  STATE" << "\n" 
    << "ATTACK    " << cmp_input.m_input_state_[GameInput::ATTACK].at(1)    << "\n"
    << "JUMP      " << cmp_input.m_input_state_[GameInput::JUMP].at(1)      << "\n"
    << "USE       " << cmp_input.m_input_state_[GameInput::USE].at(1)       << "\n"
    << "SELECT    " << cmp_input.m_input_state_[GameInput::SELECT].at(1)    << "\n"
    << "START     " << cmp_input.m_input_state_[GameInput::START].at(1)     << "\n";

    //buffer_input_
    ss
    << "CIRCULAR BUFFER: ";
    for (auto& input : cmp_input.buffer_input_.getOrderedBuffer()) {
        ss << cmp_input.m_input_string[input] << " ";
    }
    ss << "\n";
    return ss;
}

std::stringstream SystemRenderText::getSSComponentFSM (ComponentFSM& cmp_FSM) const {
    std::stringstream ss;

    ss
    << "MOVEMENT\n"
    << "Last State: "    << m_statemove_to_string.at(static_cast<StateMove>(cmp_FSM.mm_FSM_.at(TypeFSM::MOVEMENT).last_state_)) << "\n"
    << "Current State: "    << m_statemove_to_string.at(static_cast<StateMove>(cmp_FSM.mm_FSM_.at(TypeFSM::MOVEMENT).current_state_)) << "\n"
    
    << "ACTION\n"
    << "Last State: "    << m_stateaction_to_string.at(static_cast<StateAction>(cmp_FSM.mm_FSM_.at(TypeFSM::ACTION).last_state_)) << "\n"
    << "Current State: "    << m_stateaction_to_string.at(static_cast<StateAction>(cmp_FSM.mm_FSM_.at(TypeFSM::ACTION).current_state_)) << "\n"
    
    << "CONDITION\n"
    << "Last State: "    << m_statecondition_to_string.at(static_cast<StateCondition>(cmp_FSM.mm_FSM_.at(TypeFSM::CONDITION).last_state_)) << "\n"
    << "Current State: "    << m_statecondition_to_string.at(static_cast<StateCondition>(cmp_FSM.mm_FSM_.at(TypeFSM::CONDITION).current_state_)) << "\n";
    
    return ss;
}