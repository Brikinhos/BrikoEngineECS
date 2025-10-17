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
        using s_m = StateMove;
        using s_a = StateAction;
        using s_c = StateCondition;
        using t = EventTransition;
               
        fsm.mm_FSM_[TypeFSM::MOVEMENT] =
        {
            {
                {
                    static_cast<std::uint8_t>(s_m::IDLE), 
                    {
                        {t::move_button_pressed, static_cast<std::uint8_t>(s_m::MOVE)},
                        {t::jump_button_pressed, static_cast<std::uint8_t>(s_m::JUMP)},
                        {t::run_move_detected,   static_cast<std::uint8_t>(s_m::RUN)}
                    },
                },
                {
                    static_cast<std::uint8_t>(s_m::JUMP), 
                    {
                        {t::entity_on_floor_detected, static_cast<std::uint8_t>(s_m::IDLE)}
                    },
                },
                {
                    static_cast<std::uint8_t>(s_m::MOVE), 
                    {

                        {t::move_button_released, static_cast<std::uint8_t>(s_m::IDLE)},
                        {t::jump_button_pressed, static_cast<std::uint8_t>(s_m::JUMP)},
                        {t::run_move_detected,   static_cast<std::uint8_t>(s_m::RUN)}
                    }
                },
                {
                    static_cast<std::uint8_t>(s_m::RUN), 
                    {

                        {t::move_button_released, static_cast<std::uint8_t>(s_m::IDLE)},
                        {t::jump_button_pressed, static_cast<std::uint8_t>(s_m::JUMP)},
                    }
                }
            },
            static_cast<std::uint8_t>(StateMove::IDLE),
            static_cast<std::uint8_t>(StateMove::IDLE)
        };

        fsm.mm_FSM_[TypeFSM::ACTION] =
        {
            {
                {
                    static_cast<std::uint8_t>(s_a::NONE), 
                    {
                        {t::attack_button_pressed, static_cast<std::uint8_t>(s_a::ATTACK)},
                        {t::use_button_pressed, static_cast<std::uint8_t>(s_a::USE)}
                    },
                },
                {
                    static_cast<std::uint8_t>(s_a::ATTACK), 
                    {
                        {t::anim_finished, static_cast<std::uint8_t>(s_a::NONE)}
                    },
                },
                {
                    static_cast<std::uint8_t>(s_a::USE), 
                    {

                        {t::anim_finished, static_cast<std::uint8_t>(s_a::NONE)}
                    }
                }
            },
            static_cast<std::uint8_t>(StateAction::NONE),
            static_cast<std::uint8_t>(StateAction::NONE)
        };

        fsm.mm_FSM_[TypeFSM::CONDITION] =
        {
            {
                {
                    static_cast<std::uint8_t>(s_c::NONE), 
                    {
                        {t::damaged_event_detected, static_cast<std::uint8_t>(s_c::DAMAGED)}
                    },
                },
                {
                    static_cast<std::uint8_t>(s_c::DAMAGED), 
                    {
                        {t::anim_finished, static_cast<std::uint8_t>(s_c::NONE)}
                    }
                }
            },
            static_cast<std::uint8_t>(StateCondition::NONE),
            static_cast<std::uint8_t>(StateCondition::NONE)
        };
        
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