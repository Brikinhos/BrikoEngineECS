#include "game/systems/render.hpp"
#include "ecs/resourcemanager.hpp"
#include "game/components/sprite.hpp"


#include "game/events/prueba.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


void SystemRender::update (ecs::EntityManager& entity_manager, ecs::EventBus& eventbus, sf::RenderWindow& window, ecs::ResourceManager& resource_manager) const noexcept {
    auto& v_sprite_component = entity_manager.getComponentVectorByType<ComponentSprite>();
    for (auto& cmp_sprite : v_sprite_component) {
        eventbus.subscribe<EventPrueba>([&window, &resource_manager](const EventPrueba& event){
            window.draw(sf::Sprite(resource_manager.getTexture(event.name_)));
        });
        window.draw(cmp_sprite.sprite);
    }
}