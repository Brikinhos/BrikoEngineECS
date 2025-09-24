#pragma once

#include <unordered_map>
#include <vector>
#include "datastructs/slotmap.hpp"
#include "aliases.hpp"
#include <memory>
#include "entity.hpp"
#include <cstdio>
#include "component.hpp"

namespace ecs {

    using IDTypeComponent = TypeInt;
   
    struct EntityManager {

        EntityManager (ecs::TypeInt max_elements)
            : MAX_ELEMENTS_(max_elements) {
            v_entities_.reserve(MAX_ELEMENTS_);
        }

        const Entity& createEntity() {
            return v_entities_.emplace_back();
        }

        template <typename TypeComponent>
        TypeComponent& addComponent(const Entity& entity) {
            auto id_entity = entity.getEntityID();
            TypeComponent component (id_entity);
            IDTypeComponent id_type_component = TypeComponent::getIDTypeComponent();  
            //Comprobar que no existe un unique_ptr de un vector de componentes. Si no, añadir el unique_ptr
            if (pool_components_.find(id_type_component) == pool_components_.end()) {
                pool_components_[id_type_component] = std::make_unique<Slotmap<TypeComponent>>(MAX_ELEMENTS_);
            }
            //Obtenemos el puntero al vector del tipo correspondiente haciendo downcasting
            Slotmap<TypeComponent>* ptr_slotmap = static_cast<Slotmap<TypeComponent>*>(pool_components_[id_type_component].get());
            //Movemos el componente al vector
            Key key = ptr_slotmap->push_back(std::move(component));
            //Añadimos el id del tipo y un puntero del componente a la tabla de la entidad, para una búsqueda más rápida en los sitemas
            m_entity_components_[id_entity][id_type_component] = key;
            //Devolvemos referencia del componente, ya dentro del vector
            return ptr_slotmap->getData(key);
        }

        template <typename TypeComponent>
        TypeComponent& addComponent(Entity&&) = delete;
    
        //o el tipo no existe o existe el tipo pero esa entidad no tiene un componente asociado de ese tipo
        template <typename TypeComponent>
        TypeComponent* getComponentFromEntity (const Entity& entity) const noexcept {
            auto ID_component = Component<TypeComponent>::getIDTypeComponent();
            auto ID_entity = entity.getEntityID();

            //Comprobamos que existe un valor para la clave dada en m_entity_components_, si no existe, devolvemos un nullptr
            auto ptr_m_ent_cmp = m_entity_components_.find(ID_entity);
            if (ptr_m_ent_cmp == m_entity_components_.end()) {
                return nullptr;
            }
            //Comprobamos que existe un valor para la clave dada en m_entity_components_.at(x).second
            // (que es un unordered_map<ID_component, Key>), si no existe, devolvemos un nullptr
            auto ptr_m_cmp_key = ptr_m_ent_cmp->second.find(ID_component);
            if (ptr_m_cmp_key == ptr_m_ent_cmp->second.end()) {
                return nullptr;
            }

            auto& key = ptr_m_cmp_key->second;
            
            auto it_pool = pool_components_.find(ID_component);
            if (it_pool == pool_components_.end() || !it_pool->second) {
                return nullptr;
            }

            auto& slotmap = static_cast<Slotmap<TypeComponent>&>(*it_pool->second);

            auto& cmp = slotmap.getData(key);
            return &cmp;
            
        }

        template <typename TypeComponent>
        std::vector<TypeComponent>& getComponentVectorByType() {
            auto id_type_component = Component<TypeComponent>::getIDTypeComponent();

            auto it_pool = pool_components_.find(id_type_component);
            if (it_pool == pool_components_.end() || !it_pool->second) {
                throw std::runtime_error("No existe Slotmap para este TypeComponent");
            }

            auto& i_slotmap = *it_pool->second; // ISlotmap&
            auto& slotmap = static_cast<Slotmap<TypeComponent>&>(i_slotmap);

            return slotmap.getDataVector(); // Devuelves referencia al vector
        }

        void printPoolComponents () const noexcept {
            for (auto const& [key, val] : pool_components_) {
                std::cout << "IDTypeComponent: "  << key << "\t";
                std::cout << "Size Vector: "      << val->size() << "\t";
                std::cout << "Size Element: "     << val->sizeElement() << "\t";
                std::cout << "Size Mem Vector: "  << val->size() * val->sizeElement() << "\t";
                std::cout << "Memory Address: "   << val->dataAddress() << "\n";   

                const char* base_ptr = static_cast<const char*>(val->dataAddress());
                if (base_ptr) {
                    for (std::size_t i = 0; i < val->size(); ++i) {
                        const char* element_ptr = base_ptr + (i * val->sizeElement());
                        std::ptrdiff_t offset = element_ptr - base_ptr;  

                        std::cout << "    Element[" << i << "] @ "
                        << static_cast<const void*>(element_ptr)
                        << "  (offset " << offset << " bytes)\n";
                    }
                } else {
                    std::cout << "    [Vector vacío]\n";
                }

                std::cout << "\n";
            }
        }
        
        void printEntityComponents () const noexcept {
            for (auto const& [key1, val1] : m_entity_components_) {
                std::cout << "ID Entity: " << key1 << "\n";
                for (auto const& [key2, val2] : val1) {
                    std::cout << "  ID Type Component: " << key2 << "\t";
                    std::cout << "  Key: idx: " << val2.idx_ << "\tgen: " << val2.gen_ << "\n";
                }
            }
        }
        

        void printEntities () const noexcept {
            for (const auto& entity : v_entities_) {
                std::cout << entity.getEntityID() << " ";
            }
            std::cout << "\n";
        }

    private:
        const TypeInt MAX_ELEMENTS_ {10};
        std::vector<Entity> v_entities_ {};  
        std::unordered_map<IDTypeComponent, std::unique_ptr<ISlotmap>> pool_components_;
        std::unordered_map<TypeInt, std::unordered_map<TypeInt, Key>> m_entity_components_;
    };
}