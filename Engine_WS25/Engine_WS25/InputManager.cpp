#include "pch.h"

#include "InputManager.hpp"

InputManager& InputManager::getInstance()
{
	static InputManager m_instance;
	return m_instance;
}

void InputManager::init()
{
    //SFML supports 100 keys
    m_isKeyDown.reserve(101);
    m_isKeyPressed.reserve(101);
    m_isKeyUp.reserve(101);
}

void InputManager::clearKeyPressed()
{
    m_isKeyPressed.clear();
}

bool InputManager::getKeyDown(sf::Keyboard::Key key)
{
    auto it = std::find(m_isKeyDown.cbegin(), m_isKeyDown.cend(), key);
    return (it != m_isKeyDown.cend());
}

bool InputManager::getKeyUp(sf::Keyboard::Key key)
{
    auto it = std::find(m_isKeyUp.cbegin(), m_isKeyUp.cend(), key);
    return (it != m_isKeyUp.cend());
}

bool InputManager::getKeyPressed(sf::Keyboard::Key key)
{
    auto it = std::find(m_isKeyPressed.cbegin(), m_isKeyPressed.cend(), key);
    return (it != m_isKeyPressed.cend());
}

void InputManager::onKeyPressed(sf::Keyboard::Key key) 
{ 
    m_isKeyDown.push_back(key);
    m_isKeyPressed.push_back(key);
    
    auto it = std::find(m_isKeyUp.cbegin(), m_isKeyUp.cend(), key);
    if (it == m_isKeyUp.end())
        m_isKeyUp.erase(it);

    return;
}
void InputManager::onKeyReleased(sf::Keyboard::Key key) 
{
    m_isKeyUp.push_back(key);

    auto it = std::find(m_isKeyDown.cbegin(), m_isKeyDown.cend(), key);
    if (it != m_isKeyDown.end())
        m_isKeyDown.erase(it);
}
