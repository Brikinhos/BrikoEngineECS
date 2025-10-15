#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>

namespace ecs {
    using TypeInt = std::size_t;
    using Coord = std::pair<TypeInt, TypeInt>;   
}

enum class EntityState {
    IDLE,
    JUMP,
    MOVE,
    RUN,
    ATTACK,
    DAMAGED
};

const std::unordered_map<EntityState, std::string> m_state_to_string {
    {EntityState::IDLE,    "IDLE"},
    {EntityState::JUMP,    "JUMP"},
    {EntityState::MOVE,    "MOVE"},
    {EntityState::RUN,     "RUN"},
    {EntityState::ATTACK,  "ATTACK"},
    {EntityState::DAMAGED, "DAMAGED"}
};

enum class EventTransition {
    move_button_pressed,
    attack_button_pressed,
    jump_button_pressed,
    use_button_pressed,
    select_button_pressed,
    start_button_pressed,
    move_button_released,
    attack_button_released,
    jump_button_released,
    use_button_released,
    select_button_released,
    start_button_released,
    run_move_detected,
    damaged_event_detected,
    entity_on_floor_detected,
    anim_finished
};

enum GameInput {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UPLEFT,
    UPRIGHT,
    DOWNLEFT,
    DOWNRIGHT,
    ATTACK,
    JUMP,
    USE,
    SELECT,
    START,
    NOMOVE
};

const std::unordered_map<GameInput, EventTransition> m_input_pressed_transition {
    {GameInput::UP,        EventTransition::move_button_pressed},
    {GameInput::DOWN,      EventTransition::move_button_pressed},
    {GameInput::LEFT,      EventTransition::move_button_pressed},
    {GameInput::RIGHT,     EventTransition::move_button_pressed},
    {GameInput::UPLEFT,    EventTransition::move_button_pressed},
    {GameInput::UPRIGHT,   EventTransition::move_button_pressed},
    {GameInput::DOWNLEFT,  EventTransition::move_button_pressed},
    {GameInput::DOWNRIGHT, EventTransition::move_button_pressed},
    {GameInput::ATTACK,    EventTransition::attack_button_pressed},
    {GameInput::JUMP,      EventTransition::jump_button_pressed},
    {GameInput::USE,      EventTransition::use_button_pressed},
    {GameInput::SELECT,   EventTransition::select_button_pressed},
    {GameInput::START,    EventTransition::start_button_pressed},
};
const std::unordered_map<GameInput, EventTransition> m_input_released_transition {
    {GameInput::UP,        EventTransition::move_button_released},
    {GameInput::DOWN,      EventTransition::move_button_released},
    {GameInput::LEFT,      EventTransition::move_button_released},
    {GameInput::RIGHT,     EventTransition::move_button_released},
    {GameInput::UPLEFT,    EventTransition::move_button_released},
    {GameInput::UPRIGHT,   EventTransition::move_button_released},
    {GameInput::DOWNLEFT,  EventTransition::move_button_released},
    {GameInput::DOWNRIGHT, EventTransition::move_button_released},
    {GameInput::ATTACK,    EventTransition::attack_button_released},
    {GameInput::JUMP,      EventTransition::jump_button_released},
    {GameInput::USE,      EventTransition::use_button_released},
    {GameInput::SELECT,   EventTransition::select_button_released},
    {GameInput::START,    EventTransition::start_button_released},
};