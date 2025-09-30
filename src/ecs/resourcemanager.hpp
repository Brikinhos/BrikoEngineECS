#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

namespace ecs {

enum class TextureName {
    Player,
    Prueba
};

struct ResourceManager {

    void insertTexture (const std::filesystem::path& filename, TextureName name) {
        sf::Texture texture(filename);
        m_textures_[name] = std::move(texture);
    }

    sf::Texture& getTexture (TextureName name) {
        return m_textures_.at(name);
    }

    std::unordered_map<TextureName, sf::Texture> m_textures_;
};

}