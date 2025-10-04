#pragma once

#include "ecs/entity.hpp"
#include "ecs/resourcemanager.hpp"
#include "ecs/entitymanager.hpp"

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