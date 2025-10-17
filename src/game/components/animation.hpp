#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

struct Condition {

};

struct Frame {

};

struct ComponentAnimation: ecs::Component<ComponentAnimation> {
    explicit ComponentAnimation (ecs::TypeInt id_entity)
        : Component (id_entity)
    {}       
    sf::Texture texture {};
    sf::Sprite sprite {texture};  
    
    std::vector<std::pair<Condition, Frame>> anim_table_;
};