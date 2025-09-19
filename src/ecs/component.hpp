#pragma once

#include "aliases.hpp"

namespace ecs {    
    /**
    * @brief Clase base de Component. Existe para poder dar un ID a cada tipo de componente,
    * el cual es pasado a través de la plantilla en Component.
    * 
    */
    struct ComponentBase {
        explicit ComponentBase (TypeInt entityID)
        : entityID_ (entityID) {
        }
        
        const TypeInt& getEntityID () const noexcept {
            return entityID_;
        }
        
        protected:
        inline static TypeInt next_id_type_component_ { 0 };
        
        private:
        TypeInt entityID_ { 0 };
    };
    
    /**
    * @brief 
    * 
    * @tparam TypeComponent 
    */
    template <typename TypeComponent>
    struct Component : ComponentBase {
        explicit Component (TypeInt entityID) 
        : ComponentBase(entityID) {
        }    
        
        static const TypeInt& getIDTypeComponent() noexcept {
            static TypeInt id_type_component_ {next_id_type_component_++};
            return id_type_component_;
        }
    };
}