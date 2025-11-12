#pragma once

#include "IComponent.hpp"
#include "InputEnum.hpp"

class InputComponent :
    public IComponent
{
public:
    InputComponent();
    virtual ~InputComponent() = default;
    void virtual update(float deltaTime) override { return; }
    sf::Vector2f getMoveInput() const { return m_moveInput; }

protected:
    sf::Vector2f m_moveInput;
    std::unordered_map<InputEnum, sf::Vector2f> m_moveInputs;
};
