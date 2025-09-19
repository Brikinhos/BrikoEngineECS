#include "ecs/entitymanager.hpp"
#include "game/components/position.hpp"
#include "game/components/velocity.hpp"
#include "game/components/life.hpp"
#include <SFML/Graphics.hpp>

struct Key;

int main () {      
    /*
    //Creamos el Entity Manager
    ecs::EntityManager entity_manager(10);
    //Creamos una entidad
    auto& e0 = entity_manager.createEntity();
    auto& e1 = entity_manager.createEntity();
    auto& e2 = entity_manager.createEntity();
    auto& e3 = entity_manager.createEntity();
    auto& e4 = entity_manager.createEntity();
    
    //Asignamos un componente
    auto& cmp_pos_0 = entity_manager.addComponent<ComponentPosition>(e0);
    auto& cmp_pos_1 = entity_manager.addComponent<ComponentPosition>(e1);
    auto& cmp_pos_2 = entity_manager.addComponent<ComponentPosition>(e2);
    auto& cmp_pos_3 = entity_manager.addComponent<ComponentPosition>(e3);    
    
    auto& cmp_vel_1 = entity_manager.addComponent<ComponentVelocity>(e1);
    
    auto& cmp_lif_0 = entity_manager.addComponent<ComponentLife>(e0);
    auto& cmp_lif_1 = entity_manager.addComponent<ComponentLife>(e1);
    
    entity_manager.printPoolComponents();    
    entity_manager.printEntityComponents();
    entity_manager.printEntities();   
    */

    

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 + CMake + VSCode!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        // pollEvent ahora devuelve un std::optional<sf::Event>
        while (auto event = window.pollEvent()) {
            // event es un std::optional<sf::Event>, por lo que se accede con *
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

