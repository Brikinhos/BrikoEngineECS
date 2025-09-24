#pragma once

#include "ecs/component.hpp"
#include <SFML/Graphics.hpp>

struct ComponentTextInfo: ecs::Component<ComponentTextInfo> {
    explicit ComponentTextInfo (ecs::TypeInt id_entity)
        : Component(id_entity)
    {}    

    sf::Font font {"E:/Proyectos SFML/BrikoEngineECS/game/fonts/ProFontWindows.ttf"};    
    sf::Text text {font};
};