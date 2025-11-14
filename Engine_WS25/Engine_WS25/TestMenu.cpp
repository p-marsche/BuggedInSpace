#include "pch.h"

#include "InputManager.hpp"
#include "TestMenu.hpp"

TestMenu::TestMenu() 
	: m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(500, 500), "Test"))
{}

void TestMenu::exit()
{
	m_window->close();
}

void TestMenu::render()
{
	m_window->clear(sf::Color::Green);
	m_window->display();
}

void TestMenu::run()
{
	while (m_window->isOpen())
	{
		InputManager::getInstance().update();
		handleEvents();

		update(0);
		render();
	}
}

void TestMenu::update(float deltaTime)
{
	if (InputManager::getInstance().getKeyPressed(InputEnum::Exit))
		exit();
	if (InputManager::getInstance().getKeyPressed(InputEnum::MenuTest))
		changeState(GameStateEnum::Game);
}

void TestMenu::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			exit();
			break;
		case sf::Event::KeyPressed:
			InputManager::getInstance().onKeyPressed(event.key.code);
			break;
		case sf::Event::KeyReleased:
			InputManager::getInstance().onKeyReleased(event.key.code);
			break;
		}
	}
}