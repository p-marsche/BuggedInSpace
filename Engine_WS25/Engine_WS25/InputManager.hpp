#pragma once

#include "InputEnum.hpp"

class InputManager
{
public:
    static InputManager& getInstance();
    void init(int playerID, const std::unordered_map<InputEnum, sf::Keyboard::Key> playerInputs);
    void update();
    void onKeyPressed(sf::Keyboard::Key);
    void onKeyReleased(sf::Keyboard::Key);
    bool getKeyDown(InputEnum input);
    bool getKeyUp(InputEnum input);
    bool getKeyPressed(InputEnum input);

private:
    std::unordered_map<InputEnum, sf::Keyboard::Key> m_playerInputs;
    std::map<sf::Keyboard::Key, bool> m_isKeyDown;
    std::map<sf::Keyboard::Key, bool> m_isKeyUp;
    std::map<sf::Keyboard::Key, bool> m_isKeyPressed;

    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager& rhv) = delete;
    InputManager& operator =(InputManager const&) = delete;
};
