#include "game/systems/FSM.hpp"
#include "FSM.hpp"
#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"

#include "game/components/FSM.hpp"
#include "game/components/input.hpp"

#include "game/events/isbuttonpressed.hpp"

void SystemFSM::update(ecs::EntityManager& entitymanager, ecs::EventBus& eventbus) {
    auto& v_cmp_FSM = entitymanager.getComponentVectorByType<ComponentFSM>();
    for (auto& cmp_FSM : v_cmp_FSM) {
        auto* cmp_input = entitymanager.getComponentFromEntityID<ComponentInput>(cmp_FSM.getEntityID());
        if (cmp_input) {
            eventbus.subscribe<EventButtonPressed>([](){});
        }   
    }
}