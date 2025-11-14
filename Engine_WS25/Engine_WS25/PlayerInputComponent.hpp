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

    std::unordered_map<sf::Keyboard::Key, InputEnum> m_inputMap;
};

