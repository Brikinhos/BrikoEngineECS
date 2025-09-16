#include "ecs/entitymanager.hpp"
#include "game/components/position.cpp"
#include "game/components/velocity.cpp"
#include "game/components/life.cpp"

struct Key;

int main () {      
    
    //Creamos el Entity Manager
    ecs::EntityManager entity_manager(10);
    //Creamos una entidad
    std::cout << "OK\n";
    auto& e0 = entity_manager.createEntity();
    auto& e1 = entity_manager.createEntity();
    auto& e2 = entity_manager.createEntity();
    auto& e3 = entity_manager.createEntity();
    auto& e4 = entity_manager.createEntity();
    std::cout << "OK\n";
    
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
    
}