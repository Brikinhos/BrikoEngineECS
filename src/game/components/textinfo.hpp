#pragma once

#include "ecs/component.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

struct ComponentTextInfo: ecs::Component<ComponentTextInfo> {
    explicit ComponentTextInfo (ecs::TypeInt id_entity)
        : Component(id_entity), text_(font_)
    {
        text_.setCharacterSize(15);
    }

    inline static const sf::Font font_ {"E:/Proyectos SFML/BrikoEngineECS/game/fonts/ProFontWindows.ttf"};
    sf::Text text_;
};