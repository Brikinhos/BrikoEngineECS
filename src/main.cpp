#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "ecs/entity.hpp"
#include "ecs/entitymanager.hpp"
#include "ecs/eventhandler.hpp"
#include "ecs/resourcemanager.hpp"
#include "game/factories/player.hpp"

#include "game/components/position.hpp"
#include "game/components/textinfo.hpp"
#include "game/components/velocity.hpp"
#include "game/components/collision.hpp"
#include "game/components/sprite.hpp"
#include "game/components/input.hpp"

#include "game/systems/rendertext.hpp"
#include "game/systems/render.hpp"
#include "game/systems/input.hpp"

struct Key;
/*
struct ComponentText {
    ComponentText (sf::Font& font)
    : text (std::move(sf::Text(font))) {
        text.setFont(font);
    }
    sf::Text text;
};

std::vector<ComponentText> v_cmp_text;
sf::Font font ("E:/Proyectos SFML/BrikoEngineECS/game/fonts/ProFontWindows.ttf");
ComponentText cmp_text(font);
cmp_text.text.setString("HI GUYS!");
v_cmp_text.push_back(std::move(cmp_text));
return 0;
}
*/

int main () {      
    
    
    //Creamos el Entity Manager
    ecs::EntityManager entity_manager(10);
    ecs::EventBus eventbus;
    ecs::ResourceManager resource_manager;
    
    resource_manager.insertTexture("E:/Proyectos SFML/BrikoEngineECS/game/assets/basun_soldier.png", ecs::TextureName::Player);
    resource_manager.insertTexture("E:/Proyectos SFML/BrikoEngineECS/game/assets/holi.png",          ecs::TextureName::Prueba);
        
    EntityBuilder entity_builder(entity_manager, resource_manager, TypeEntity::PLAYER);
    
    entity_builder
    .withCollision( 0, 0, 30, 52)
    .withPosition(50, 50)
    .withSprite(ecs::TextureName::Player)
    .withVelocity(5)
    .with<ComponentInput>()
    .with<ComponentTextInfo>();

    entity_manager.printEntities();
    entity_manager.printEntityComponents();
    entity_manager.printPoolComponents();        
    
    SystemRenderText sys_text;
    SystemRender sys_render;
    SystemInput sys_input;
    
    sf::Clock clock;
    
    sf::RenderWindow window(sf::VideoMode({800, 600}), "BASÚN 2");
    window.setFramerateLimit(120);
    
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
            window.close();
        }
        
        float dt = clock.restart().asSeconds();
     
        sf::Color color(255,165,0);
        window.clear(color);
        sys_input.update(entity_manager, eventbus);
        //sys_IA.update(entity_manager, eventbus);
        //sys_physics.update(entity_manager, eventbus);
        //sys_collision.update(entity_manager, eventbus);
        //sys_FSM.update(entity_manager, eventbus);
        //sys_animation(entity_manager, eventbus);
        sys_text.update(entity_manager, eventbus, window);
        sys_render.update(entity_manager, eventbus, window, resource_manager);
        eventbus.processQueue();
        window.display();
    }
    
    return 0;
}


