#include "game/systems/render.hpp"
#include "ecs/resourcemanager.hpp"
#include "game/components/sprite.hpp"

#include "game/events/statechanged.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


void SystemRender::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus, sf::RenderWindow& window, ecs::ResourceManager& resource_manager) const noexcept {
    auto& v_sprite_component = entity_manager.getComponentVectorByType<ComponentSprite>();
    for (auto& cmp_sprite : v_sprite_component) {
        
        window.draw(cmp_sprite.sprite);

    }
}