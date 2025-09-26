#pragma once

#include "ecs/component.hpp"
#include "ecs/aliases.hpp"
#include "datastructs/circularbuffer.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

enum GameInput {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ATTACK,
    JUMP,
    USE,
    SELECT,
    START
};

struct Input {

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
        
        m_input_state_[GameInput::UP]     = false;
        m_input_state_[GameInput::DOWN]   = false;
        m_input_state_[GameInput::LEFT]   = false;
        m_input_state_[GameInput::RIGHT]  = false;
        m_input_state_[GameInput::ATTACK] = false;
        m_input_state_[GameInput::JUMP]   = false;
        m_input_state_[GameInput::USE]    = false;
        m_input_state_[GameInput::SELECT] = false;
        m_input_state_[GameInput::START]  = false;        
    }
    
    CircularBuffer<Input, 10> buffer_input_;
    CircularBuffer<std::int64_t, 10> buffer_time_;
    std::unordered_map<GameInput, sf::Keyboard::Key> m_bind_keyboard_;
    std::unordered_map<GameInput, bool> m_input_state_;
    std::unordered_map<GameInput, bool> m_virtualinput_state_;
};