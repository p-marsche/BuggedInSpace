#pragma once

#include "InputEnum.hpp"
#include "pch.h"

class InputManager
{
public:
    static InputManager& getInstance();
    void init();
    void update();
    void onKeyPressed(sf::Keyboard::Key);
    void onKeyReleased(sf::Keyboard::Key);
    bool getKeyDown(InputEnum input, int player);
    bool getKeyUp(InputEnum input, int player);
    bool getKeyPressed(InputEnum input, int player);

private:
    std::unordered_map<InputEnum, sf::Keyboard::Key> m_inputsPlayer1;
    std::unordered_map<InputEnum, sf::Keyboard::Key> m_inputsPlayer2;
    std::map<sf::Keyboard::Key, bool> m_isKeyDown;
    std::map<sf::Keyboard::Key, bool> m_isKeyUp;
    std::map<sf::Keyboard::Key, bool> m_isKeyPressed;

    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager& rhv) = delete;
    InputManager& operator =(InputManager const&) = delete;
};
