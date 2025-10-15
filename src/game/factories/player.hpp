#pragma once

#include "ecs/aliases.hpp"
#include "ecs/entity.hpp"
#include "ecs/resourcemanager.hpp"
#include "ecs/entitymanager.hpp"

#include "game/components/FSM.hpp"
#include "game/components/collision.hpp"
#include "game/components/position.hpp"
#include "game/components/velocity.hpp"
#include "game/components/position.hpp"
#include "game/components/sprite.hpp"

class EntityBuilder {
public:
    EntityBuilder(ecs::EntityManager& em, ecs::ResourceManager& rm, TypeEntity type_entity)
        : entity_manager(em), resource_manager(rm), entity(entity_manager.createEntity(type_entity)) {

    }

    EntityBuilder& withCollision(float ax, float ay, float bx, float by) {
        auto& col = entity_manager.addComponent<ComponentCollision>(entity);
        col.box.coord_a_ = {ax, ay};
        col.box.coord_b_ = {bx, by};
        return *this;
    }

    EntityBuilder& withPosition(float x, float y) {
        auto& pos = entity_manager.addComponent<ComponentPosition>(entity);
        pos.x = x;
        pos.y = y;
        return *this;
    }

    EntityBuilder& withVelocity(float v) {
        auto& vel = entity_manager.addComponent<ComponentVelocity>(entity);
        vel.velocity = v;
        return *this;
    }

    EntityBuilder& withSprite(ecs::TextureName tex) {
        auto& spr = entity_manager.addComponent<ComponentSprite>(entity);
        spr.sprite.setTexture(resource_manager.getTexture(tex));
        spr.sprite.setTextureRect({{0,0},{32,50}});
        spr.sprite.setPosition({200, 200});
        spr.sprite.setScale({4, 4});
        return *this;
    }

    EntityBuilder& withFSM() {
        auto& fsm = entity_manager.addComponent<ComponentFSM>(entity);
        using s = EntityState;
        using t = EventTransition;
               
        fsm.m_FSM_[s::IDLE]    [t::damaged_event_detected]   = s::DAMAGED;
        fsm.m_FSM_[s::IDLE]    [t::jump_button_pressed]      = s::JUMP;
        fsm.m_FSM_[s::IDLE]    [t::attack_button_pressed]    = s::ATTACK;
        fsm.m_FSM_[s::IDLE]    [t::move_button_pressed]      = s::MOVE;
        fsm.m_FSM_[s::IDLE]    [t::run_move_detected]        = s::RUN;
        fsm.m_FSM_[s::MOVE]    [t::move_button_released]     = s::IDLE;
        fsm.m_FSM_[s::MOVE]    [t::attack_button_pressed]    = s::ATTACK;
        fsm.m_FSM_[s::MOVE]    [t::damaged_event_detected]   = s::DAMAGED;
        fsm.m_FSM_[s::MOVE]    [t::jump_button_pressed]      = s::JUMP;
        fsm.m_FSM_[s::MOVE]    [t::run_move_detected]        = s::RUN;
        fsm.m_FSM_[s::ATTACK]  [t::anim_finished]            = s::IDLE;
        fsm.m_FSM_[s::ATTACK]  [t::damaged_event_detected]   = s::DAMAGED;
        fsm.m_FSM_[s::DAMAGED] [t::anim_finished]            = s::IDLE;
        fsm.m_FSM_[s::JUMP]    [t::damaged_event_detected]   = s::DAMAGED;
        fsm.m_FSM_[s::JUMP]    [t::entity_on_floor_detected] = s::IDLE;
        fsm.m_FSM_[s::RUN]     [t::damaged_event_detected]   = s::DAMAGED;
        fsm.m_FSM_[s::RUN]     [t::attack_button_pressed]    = s::ATTACK;
        fsm.m_FSM_[s::RUN]     [t::move_button_released]     = s::IDLE;
        fsm.m_FSM_[s::RUN]     [t::jump_button_pressed]      = s::JUMP;
        
        return *this;
    }

    template<typename T>
    EntityBuilder& with() {
        entity_manager.addComponent<T>(entity);
        return *this;
    }

    const ecs::Entity& build() { return entity; }

private:
    ecs::EntityManager& entity_manager;
    ecs::ResourceManager& resource_manager;
    const ecs::Entity& entity;
};