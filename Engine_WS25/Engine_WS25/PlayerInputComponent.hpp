#pragma once

#include "InputComponent.hpp"
#include "InputEnum.hpp"

#include <SFML/Graphics.hpp>

#include <unordered_map>

class PlayerInputComponent :
    public InputComponent
{
public:
    PlayerInputComponent(int playerNumber);
    ~PlayerInputComponent() = default;
    void update(float deltaTime) override;

private:
    int m_playerNumber;
};

