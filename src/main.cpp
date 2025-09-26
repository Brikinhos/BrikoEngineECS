#include "ecs/entitymanager.hpp"
#include "game/components/position.hpp"
#include "game/components/textinfo.hpp"
#include "game/components/velocity.hpp"
#include "game/components/collision.hpp"
#include "game/components/sprite.hpp"
#include "game/components/input.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "datastructs/circularbuffer.hpp"
#include "game/systems/rendertext.hpp"

struct Key;

int main () {      
    //Creamos el Entity Manager
    ecs::EntityManager entity_manager(10);
    //Creamos una entidad
   //auto& player = entity_manager.createEntity();
    auto& mongolin = entity_manager.createEntity();

    
    auto& txt2 = entity_manager.addComponent<ComponentTextInfo>(mongolin);
    std::cout << "Dirección txt: " << static_cast<const void*>(&txt2) << "\n";
    auto& inp2 = entity_manager.addComponent<ComponentInput>(mongolin);
    std::cout << "Dirección inp: " << static_cast<const void*>(&inp2) << "\n";



    
/*
auto& col = entity_manager.addComponent<ComponentCollision>(player);
col.box.coord_a_ = {0, 0};
col.box.coord_b_ = {50, 50};

auto& pos = entity_manager.addComponent<ComponentPosition>(player);
pos.x = 200;
pos.y = 200;

auto& vel = entity_manager.addComponent<ComponentVelocity>(player);
vel.velocity = 200;

auto& spr = entity_manager.addComponent<ComponentSprite>(player);
auto yes = spr.texture.loadFromFile("E:/Proyectos SFML/BrikoEngineECS/game/assets/basun_soldier.png");

spr.sprite.setTexture(spr.texture);
spr.sprite.setTextureRect({{0, 0},{30, 52}});
spr.sprite.setPosition({200, 200});
spr.sprite.setScale({4, 4});

auto& inp = entity_manager.addComponent<ComponentInput>(player);
auto& txt = entity_manager.addComponent<ComponentTextInfo>(player);       



sf::RectangleShape rect;
rect.setSize({50, 100});
rect.setPosition({200, 200});

entity_manager.printEntityComponents();
entity_manager.printPoolComponents();
*/
sf::RenderWindow window(sf::VideoMode({800, 600}), "BASÚN 2");
window.setFramerateLimit(120);

SystemRenderText sys_text;

float speed = 200.f; // píxeles por segundo
sf::Clock clock;

while (window.isOpen()) {
    while (auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
        window.close();
    }
    
        float dt = clock.restart().asSeconds();
        /*
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            rect.move({0, -speed * dt});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            rect.move({0, speed * dt});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            rect.move({-speed * dt, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            rect.move({speed * dt, 0});
        }        
        */

        window.clear(sf::Color::Yellow);
        sys_text.update(entity_manager, window);
        window.display();
    }
    
    return 0;
}

