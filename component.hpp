#pragma once

#include "aliases.hpp"
#include <vector>

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
    
template <typename TypeComponent>
struct Component : ComponentBase {
    explicit Component (TypeInt entityID) 
    : ComponentBase(entityID) {
    }    
    
    static const TypeInt& getIDTypeComponent() noexcept {
        static TypeInt id_type_component_ {next_id_type_component_++};
        return id_type_component_;
    }
    
    virtual std::size_t sizeOfComponentInBytes() {
        return 0;
    }
};