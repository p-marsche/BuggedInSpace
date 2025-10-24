#pragma once

#include <SFML/Window.hpp>

#include <unordered_map>

class InputManager
{
public:
    static InputManager& GetInstance();
    void Init(sf::Window& window);
    void Update();
    bool GetKeyDown(sf::Keyboard::Key key);
    bool GetKeyUp(sf::Keyboard::Key key);
    bool GetKeyPressed(sf::Keyboard::Key key);

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager& rhv) = delete;
    InputManager& operator=(InputManager const&) = delete;

    void OnKeyPressed();
    void OnKeyReleased();

    std::unordered_map<sf::Keyboard::Key, bool> isKeyDown;
    std::unordered_map<sf::Keyboard::Key, bool> isKeyUp;
    std::unordered_map<sf::Keyboard::Key, bool> isKeyPressed;
};

