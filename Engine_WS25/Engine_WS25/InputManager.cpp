#include "InputManager.h"

InputManager& InputManager::GetInstance()
{
	static InputManager m_instance;
	return m_instance;
}

void InputManager::Init(sf::Window& window)
{
	window.setKeyRepeatEnabled(false);
	//sf::Event::KeyPressed += OnKeyPressed;
	//sf::Event::KeyReleased += OnKeyReleased;

    isKeyDown.insert({ sf::Keyboard::Key::W, false });
    isKeyDown.insert({ sf::Keyboard::Key::A, false });
    isKeyDown.insert({ sf::Keyboard::Key::S, false });
    isKeyDown.insert({ sf::Keyboard::Key::D, false });

    isKeyUp.insert({ sf::Keyboard::Key::W, false });
    isKeyUp.insert({ sf::Keyboard::Key::A, false });
    isKeyUp.insert({ sf::Keyboard::Key::S, false });
    isKeyUp.insert({ sf::Keyboard::Key::D, false });

    isKeyPressed.insert({ sf::Keyboard::Key::W, false });
    isKeyPressed.insert({ sf::Keyboard::Key::A, false });
    isKeyPressed.insert({ sf::Keyboard::Key::S, false });
    isKeyPressed.insert({ sf::Keyboard::Key::D, false });
}

void InputManager::Update()
{
    for (auto& [_, flag] : isKeyDown)
        flag = false;

    for (auto& [_, flag] : isKeyUp)
        flag = false;
}

bool InputManager::GetKeyDown(sf::Keyboard::Key key)
{
    return (isKeyDown.find(key) != isKeyDown.end()) ? isKeyDown[key] : false;
}

bool InputManager::GetKeyUp(sf::Keyboard::Key key)
{
    return (isKeyUp.find(key) != isKeyUp.end()) ? isKeyUp[key] : false;
}

bool InputManager::GetKeyPressed(sf::Keyboard::Key key)
{
    return (isKeyPressed.find(key) != isKeyPressed.end()) ? isKeyPressed[key] : false;
}

void InputManager::OnKeyPressed() { }
void InputManager::OnKeyReleased() { }