#pragma once

#include <unordered_map>
#include <vector>
#include "../datastructs/slotmap.hpp"
#include "aliases.hpp"
#include <memory>
#include "entity.hpp"
#include <cstdio>
#include <type_traits>


namespace ecs {

    template <typename TypeComponent>
    struct Component;
    using IDTypeComponent = TypeInt;

    //template <typename TypeComponent>
    //using VectorComponent = std::vector<Component<TypeComponent>>;

    /*
    struct IVectorComponent {
        virtual ~IVectorComponent() = default;
        virtual std::size_t size() const noexcept = 0;
        virtual std::size_t sizeElement() const noexcept = 0;
        virtual const void* dataAddress() const noexcept = 0;
    };

    template <typename T>
    struct VectorComponent : IVectorComponent {
        VectorComponent (const TypeInt max_elements) {
            vector_component_.reserve(max_elements);
        }

        std::size_t size() const noexcept override{
            return vector_component_.size();
        }

        std::size_t sizeElement() const noexcept override{
            return sizeof(vector_component_[0]);
        }

        const void* dataAddress() const noexcept override {
            return vector_component_.empty() ? nullptr 
            : static_cast<const void*>(vector_component_.data());
        }

        std::vector<T> vector_component_;
    };

    */
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
            //Comprobamos que TypeComponent sea hija de Component<TypeComponent>
            static_assert(std::is_base_of<Component<TypeComponent>, TypeComponent>::value, "El componente no hereda de Component<TypeComponent>");
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
        
    /*
    template <typename TypeComponent>
    TypeComponent* getComponentFromEntityComponentsTable (const Entity& entity) const noexcept {
            auto ID_component = Component<TypeComponent>::getIDTypeComponent();
            auto e_ID = entity.getEntityID();
            auto it_cmp = m_entity_components_.at(e_ID).find(ID_component);
            if (it_cmp != m_entity_components_.at(e_ID).end())
            return static_cast<TypeComponent*>(it_cmp->second);
            return nullptr;
        }

        template <typename TypeComponent>
        void addComponentToEntityComponentsTable (const TypeComponent& component, const Entity& entity) noexcept {
            auto* ptr_cmp = &component;
            auto id_type_cmp = Component<TypeComponent>::getIDTypeComponent();
            auto e_ID = entity.getEntityID();
            m_entity_components_[e_ID][id_type_cmp] = ptr_cmp;
        }

        */

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
                        std::ptrdiff_t offset = element_ptr - base_ptr;  // ✅ válido: char* - char*

                        std::cout << "    Element[" << i << "] @ "
                        << static_cast<const void*>(element_ptr)  // mostramos como void* para formato bonito
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
                    std::cout << "  Key for SlotMap:\t Idx: " << val2.idx_ << "\tGen: " << val2.gen_ << "\n";
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
        const TypeInt MAX_ELEMENTS_ {};
        std::vector<Entity> v_entities_ {};  
        std::unordered_map<IDTypeComponent, std::unique_ptr<ISlotmap>> pool_components_;
        std::unordered_map<TypeInt, std::unordered_map<TypeInt, Key>> m_entity_components_;
    };
}