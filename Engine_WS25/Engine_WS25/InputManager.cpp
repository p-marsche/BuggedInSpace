#include "pch.h"

#include "InputManager.hpp"

InputManager& InputManager::getInstance()
{
	static InputManager m_instance;
	return m_instance;
}

void InputManager::init()
{
    m_inputsPlayer1.emplace(InputEnum::Up, sf::Keyboard::Key::W);
    m_inputsPlayer1.emplace(InputEnum::Left, sf::Keyboard::Key::A);
    m_inputsPlayer1.emplace(InputEnum::Down, sf::Keyboard::Key::S);
    m_inputsPlayer1.emplace(InputEnum::Right, sf::Keyboard::Key::D);
    m_inputsPlayer1.emplace(InputEnum::Shoot, sf::Keyboard::Key::Space);

    m_inputsPlayer2.emplace(InputEnum::Up, sf::Keyboard::Key::Up);
    m_inputsPlayer2.emplace(InputEnum::Left, sf::Keyboard::Key::Left);
    m_inputsPlayer2.emplace(InputEnum::Down, sf::Keyboard::Key::Down);
    m_inputsPlayer2.emplace(InputEnum::Right, sf::Keyboard::Key::Right);
    m_inputsPlayer2.emplace(InputEnum::Shoot, sf::Keyboard::Key::Num0);

    for (auto& [_, key] : m_inputsPlayer1)
    {
        m_isKeyDown.emplace(key, false);
        m_isKeyUp.emplace(key, false);
        m_isKeyPressed.emplace(key, false);
    }

    for (auto& [_, key] : m_inputsPlayer2)
    {
        m_isKeyDown.emplace(key, false);
        m_isKeyUp.emplace(key, false);
        m_isKeyPressed.emplace(key, false);
    }
}

void InputManager::update()
{
    for (auto& [_, flag] : m_isKeyPressed)
        flag = false;
}

bool InputManager::getKeyDown(InputEnum input, int player)
{
    if (player != 1 && player != 2)
        return false;

    if (player == 1)
    {
        auto result = m_inputsPlayer1.find(input);
        if (result == m_inputsPlayer1.end())
            return false;

        return m_isKeyDown.at(result->second);
    }
    else
    {
        auto result = m_inputsPlayer2.find(input);
        if (result == m_inputsPlayer2.end())
            return false;

        return m_isKeyDown.at(result->second);
    }
}

bool InputManager::getKeyUp(InputEnum input, int player)
{
    if (player != 1 && player != 2)
        return false;

    if (player == 1)
    {
        auto result = m_inputsPlayer1.find(input);
        if (result == m_inputsPlayer1.end())
            return false;

        return m_isKeyUp.at(result->second);
    }
    else
    {
        auto result = m_inputsPlayer2.find(input);
        if (result == m_inputsPlayer2.end())
            return false;

        return m_isKeyUp.at(result->second);
    }
}

bool InputManager::getKeyPressed(InputEnum input, int player)
{
    if (player != 1 && player != 2)
        return false;

    if (player == 1)
    {
        auto result = m_inputsPlayer1.find(input);
        if (result == m_inputsPlayer1.end())
            return false;

        return m_isKeyPressed.at(result->second);
    }
    else
    {
        auto result = m_inputsPlayer2.find(input);
        if (result == m_inputsPlayer2.end())
            return false;

        return m_isKeyPressed.at(result->second);
    }
}

void InputManager::onKeyPressed(sf::Keyboard::Key key) 
{ 
    if (m_isKeyPressed.find(key) == m_isKeyPressed.end())
        return;
    
    m_isKeyPressed.at(key) = true;
    m_isKeyDown.at(key) = true;
    m_isKeyUp.at(key) = false;
}
void InputManager::onKeyReleased(sf::Keyboard::Key key) 
{
    if (m_isKeyPressed.find(key) == m_isKeyPressed.end())
        return;

    m_isKeyDown.at(key) = false;
    m_isKeyUp.at(key) = true;
}
