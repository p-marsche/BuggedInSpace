#pragma once

#include "IComponent.hpp"
#include "InputEnum.hpp"

class InputComponent :
    public IComponent
{
public:
    InputComponent(int playerNumber);
    ~InputComponent() = default;
    void update(float deltaTime) override;
    sf::Vector2f getMoveInput() { return m_moveInput; }

private:
    int m_playerNumber;
    sf::Vector2f m_moveInput;
    std::unordered_map<InputEnum, sf::Vector2f> m_moveInputs;
};
