#pragma once

#include "InputEnum.hpp"

class InputManager
{
public:
    static InputManager& getInstance();
    void init();
    void clearKeyPressed();
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    bool getKeyDown(sf::Keyboard::Key);
    bool getKeyUp(sf::Keyboard::Key key);
    bool getKeyPressed(sf::Keyboard::Key key);

private:
    std::vector<sf::Keyboard::Key> m_isKeyDown;
    std::vector<sf::Keyboard::Key> m_isKeyUp;
    std::vector<sf::Keyboard::Key> m_isKeyPressed;

    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager& rhv) = delete;
    InputManager& operator =(InputManager const&) = delete;
};
