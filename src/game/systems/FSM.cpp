#include "game/systems/FSM.hpp"
#include "FSM.hpp"
#include "ecs/aliases.hpp"
#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

#include "game/components/FSM.hpp"
#include "game/components/input.hpp"

#include "game/events/buttonreleased.hpp"
#include "game/events/buttonpressed.hpp"

void SystemFSM::update(ecs::EntityManager& entitymanager, ecs::EventBus& eventbus_input) {
    eventbus_input.processQueue();    
}

void SystemFSM::init(ecs::EntityManager& entitymanager, ecs::EventBus& eventbus_input) {
    eventbus_input.subscribe<EventButtonReleased>([&entitymanager](const EventButtonReleased& event){
        std::cout << "call fn event released\n";
        auto* cmp_FSM     = entitymanager.getComponentFromEntityID<ComponentFSM>  (event.entity_);
        auto* cmp_input = entitymanager.getComponentFromEntityID<ComponentInput>(event.entity_);
        if (cmp_FSM && cmp_input) {
            auto& transition = m_input_released_transition.at(event.input_);
            //Por cada FSM
            for (auto& [TypeFSM, FSM] : cmp_FSM->mm_FSM_) {
                auto& m_FSM = FSM.m_FSM_;
                for (auto& m_transition : m_FSM.at(FSM.current_state_)) {
                    if (m_transition.first == transition) {
                        auto& next_state = m_FSM.at(FSM.current_state_).at(transition);
                        FSM.last_state_ = FSM.current_state_;
                        FSM.current_state_ = next_state;
                    }
                }
            }
        }        
    });

    eventbus_input.subscribe<EventButtonPressed>([&entitymanager](const EventButtonPressed& event){
        std::cout << "call fn event pressed\n";
        auto* cmp_FSM     = entitymanager.getComponentFromEntityID<ComponentFSM>  (event.entity_);
        auto* cmp_input = entitymanager.getComponentFromEntityID<ComponentInput>(event.entity_);
        if (cmp_FSM && cmp_input) {
            auto& transition = m_input_pressed_transition.at(event.input_);
            //Por cada FSM
            for (auto& [TypeFSM, FSM] : cmp_FSM->mm_FSM_) {
                auto& m_FSM = FSM.m_FSM_;
                for (auto& m_transition : m_FSM.at(FSM.current_state_)) {
                    if (m_transition.first == transition) {
                        auto& next_state = m_FSM.at(FSM.current_state_).at(transition);
                        FSM.last_state_ = FSM.current_state_;
                        FSM.current_state_ = next_state;
                    }
                }
            }
        }         
    });
}