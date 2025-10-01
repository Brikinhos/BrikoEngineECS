#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"
#include "datastructs/circularbuffer.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <string>
#include <unordered_map>

enum GameInput {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPRIGHT,
    UPLEFT,
    DOWNRIGHT,
    DOWNLEFT,
    ATTACK,
    JUMP,
    USE,
    SELECT,
    START,
    NOMOVE
};

struct ComponentInput : ecs::Component<ComponentInput> {
    explicit ComponentInput (ecs::TypeInt id_entity)
        : Component(id_entity)
    {
        m_bind_keyboard_[GameInput::UP]     = sf::Keyboard::Key::W;
        m_bind_keyboard_[GameInput::DOWN]   = sf::Keyboard::Key::S;
        m_bind_keyboard_[GameInput::LEFT]   = sf::Keyboard::Key::A;
        m_bind_keyboard_[GameInput::RIGHT]  = sf::Keyboard::Key::D;
        m_bind_keyboard_[GameInput::ATTACK] = sf::Keyboard::Key::LControl;
        m_bind_keyboard_[GameInput::JUMP]   = sf::Keyboard::Key::Space;
        m_bind_keyboard_[GameInput::USE]    = sf::Keyboard::Key::E;
        m_bind_keyboard_[GameInput::SELECT] = sf::Keyboard::Key::RShift;
        m_bind_keyboard_[GameInput::START]  = sf::Keyboard::Key::Enter;
        
        m_input_state_[GameInput::UP]     = {false, false};
        m_input_state_[GameInput::DOWN]   = {false, false};
        m_input_state_[GameInput::LEFT]   = {false, false};
        m_input_state_[GameInput::RIGHT]  = {false, false};
        m_input_state_[GameInput::ATTACK] = {false, false};
        m_input_state_[GameInput::JUMP]   = {false, false};
        m_input_state_[GameInput::USE]    = {false, false};
        m_input_state_[GameInput::SELECT] = {false, false};
        m_input_state_[GameInput::START]  = {false, false};        
    }
    
    CircularBuffer<GameInput, 10> buffer_input_;
    CircularBuffer<std::int64_t, 10> buffer_time_;
    std::unordered_map<GameInput, sf::Keyboard::Key> m_bind_keyboard_;
    using PressedLastFrame = bool;
    using PressedThisFrame = bool;
    std::unordered_map<GameInput, std::pair<PressedLastFrame, PressedThisFrame>> m_input_state_;
    using UP = bool;
    using DOWN = bool;
    using LEFT = bool;
    using RIGHT = bool;
    inline static const std::unordered_map<ecs::TypeInt, GameInput> truthtable_input_directions_ {
        {0,  GameInput::NOMOVE},
        {1,  GameInput::RIGHT},
        {2,  GameInput::LEFT}, 
        {3,  GameInput::NOMOVE}, 
        {4,  GameInput::DOWN}, 
        {5,  GameInput::DOWNRIGHT}, 
        {6,  GameInput::DOWNLEFT}, 
        {7,  GameInput::DOWN}, 
        {8,  GameInput::UP}, 
        {9,  GameInput::UPRIGHT}, 
        {10, GameInput::UPLEFT}, 
        {11, GameInput::UP}, 
        {12, GameInput::NOMOVE}, 
        {13, GameInput::RIGHT}, 
        {14, GameInput::LEFT},
        {15, GameInput::NOMOVE} 
    };

    std::unordered_map<GameInput, std::string> m_input_string {
    { GameInput::UP,        "UP" },
    { GameInput::DOWN,      "DW" },
    { GameInput::LEFT,      "LF" },
    { GameInput::RIGHT,     "RG" },
    { GameInput::UPRIGHT,   "UR" },
    { GameInput::UPLEFT,    "UL" },
    { GameInput::DOWNRIGHT, "DR" },
    { GameInput::DOWNLEFT,  "DL" },
    { GameInput::ATTACK,    "AT" },        
    { GameInput::JUMP,      "JP" },
    { GameInput::USE,      "US" },
    { GameInput::SELECT,   "SL"},
    { GameInput::START,    "ST"},
    { GameInput::NOMOVE,   ""  }
    };
};