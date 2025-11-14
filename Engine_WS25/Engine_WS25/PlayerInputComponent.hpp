#pragma once

#include "IComponent.hpp"
#include "InputEnum.hpp"
#include "SFML/Window.hpp"
#include <unordered_map>

class PlayerInputComponent :
    public IComponent
{
public:
    PlayerInputComponent(int entityID, std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap);

    virtual ComponentType GetType() override { return m_type; }

    static constexpr ComponentType m_type = ComponentType::PlayerInput;

    std::unordered_map<sf::Keyboard::Key, InputEnum> m_inputMap;
};

