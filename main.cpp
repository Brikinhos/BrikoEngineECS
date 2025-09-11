#include "slotmap.hpp"
#include <cstdint>
#include "entitymanager.hpp"


struct Key;

int main () {      
    
    struct ComponentPosition : Component<ComponentPosition> {
        explicit ComponentPosition (TypeInt id_entity)
        : Component(id_entity)
        {}
        
        std::size_t sizeOfComponentInBytes () override {
            return sizeof(*this);
        }
        
        std::uint64_t x {};
        std::uint64_t y {};
        std::uint64_t a {};
        std::uint64_t b {};
        std::uint64_t c {};
        std::uint64_t d {};
    };
    
    struct ComponentVelocity : Component<ComponentVelocity> {
        explicit ComponentVelocity (TypeInt id_entity)
        : Component(id_entity)
        {}
        
        std::size_t sizeOfComponentInBytes () override {
            return sizeof(*this);
        }
        
        std::uint64_t v {};
    };
    
    struct ComponentLife : Component<ComponentLife> {
        explicit ComponentLife (TypeInt id_entity)
        : Component(id_entity)
        {}
        
        std::size_t sizeOfComponentInBytes () override {
            return sizeof(*this);
        }
        
        std::uint64_t l {};
    };
    
    
    //Creamos el Entity Manager
    EntityManager entity_manager;
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
    
    auto& cmp_vel_0 = entity_manager.addComponent<ComponentVelocity>(e0);
    auto& cmp_vel_1 = entity_manager.addComponent<ComponentVelocity>(e1);
    auto& cmp_vel_2 = entity_manager.addComponent<ComponentVelocity>(e2);
    
    auto& cmp_lif_0 = entity_manager.addComponent<ComponentLife>(e0);
    auto& cmp_lif_1 = entity_manager.addComponent<ComponentLife>(e1);
    
    
    entity_manager.printPoolComponents();
    
    //entity_manager.printEntityComponents();
    entity_manager.printEntities();   
}