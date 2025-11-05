#pragma once

#include <map>
#include <unordered_map>

#include <SFML/Window.hpp>

#include "InputEnum.h"

class InputManager
{
public:
    static InputManager& GetInstance();
    void Init();
    void Update();
    void OnKeyPressed(sf::Keyboard::Key);
    void OnKeyReleased(sf::Keyboard::Key);
    bool GetKeyDown(InputEnum input, int player);
    bool GetKeyUp(InputEnum input, int player);
    bool GetKeyPressed(InputEnum input, int player);

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager& rhv) = delete;
    InputManager& operator=(InputManager const&) = delete;

    std::unordered_map<InputEnum, sf::Keyboard::Key> m_inputsPlayer1;
    std::unordered_map<InputEnum, sf::Keyboard::Key> m_inputsPlayer2;
    std::map<sf::Keyboard::Key, bool> m_isKeyDown;
    std::map<sf::Keyboard::Key, bool> m_isKeyUp;
    std::map<sf::Keyboard::Key, bool> m_isKeyPressed;
};

