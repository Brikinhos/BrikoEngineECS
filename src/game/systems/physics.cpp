#include "game/systems/physics.hpp"

#include "game/components/input.hpp"
#include "game/components/position.hpp"

void SystemPhysics::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus) const noexcept {
    auto& v_cmp_position = entity_manager.getComponentVectorByType<ComponentPosition>();
    for (auto& cmp_position : v_cmp_position) {
        auto* cmp_input = entity_manager.getComponentFromEntityID<ComponentInput>(cmp_position.getEntityID());
        if (cmp_input) {
           
            
        }
    }
}