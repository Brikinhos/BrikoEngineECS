#include "game/systems/render.hpp"
#include "game/components/sprite.hpp"


void SystemRender::update (ecs::EntityManager& entity_manager, sf::RenderWindow& window) const noexcept {
    auto& v_sprite_component = entity_manager.getComponentVectorByType<ComponentSprite>();
    for (auto& cmp_sprite : v_sprite_component) {
        window.draw(cmp_sprite.sprite);
    }
}