#include "pch.h"

#include "InputManager.hpp"

InputManager& InputManager::getInstance()
{
	static InputManager m_instance;
	return m_instance;
}

void InputManager::init(int playerOneID, const std::unordered_map<InputEnum, sf::Keyboard::Key> playerInputs)
{
    m_playerInputs = playerInputs;
    for (auto& [_, key] : m_playerInputs)
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

bool InputManager::getKeyDown(InputEnum input)
{
        auto result = m_playerInputs.find(input);
        if (result == m_playerInputs.end())
            return false;

        return m_isKeyDown.at(result->second);
}

bool InputManager::getKeyUp(InputEnum input)
{
        auto result = m_playerInputs.find(input);
        if (result == m_playerInputs.end())
            return false;

        return m_isKeyUp.at(result->second);
}

bool InputManager::getKeyPressed(InputEnum input)
{
        auto result = m_playerInputs.find(input);
        if (result == m_playerInputs.end())
            return false;

        return m_isKeyPressed.at(result->second);
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
