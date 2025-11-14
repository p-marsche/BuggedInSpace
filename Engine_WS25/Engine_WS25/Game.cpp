#include "pch.h"

#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "EntityFactory.hpp"
#include "Registry.hpp"
#include "VectorUtils.hpp"

Game::Game()
	: WIDTH(1280)
	, HEIGHT(720)
	, TITLE("Engine_WS25")
	, m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE))
	, m_clock()
	, m_cameraScrollTime(0.f)
	, m_maxScrollTime(100.f)
	, m_projectileCount(0)
{
	m_window->setFramerateLimit(60);
	m_window->setKeyRepeatEnabled(false);
	m_aspectRatio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
}

void Game::run()
{
	initialize();
	float deltaTime = 0.f;

	while (m_window->isOpen())
	{
		InputManager::getInstance().update();
		handleEvents();

		deltaTime = m_clock.restart().asSeconds();
		update(deltaTime);
		render();
	}
}

void Game::initialize()
{
	//InputManager::getInstance().init();
}

void Game::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				exit();
				break;
			case sf::Event::Resized:
				resizeWindow(event.size.width, event.size.height);
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

void Game::update(float deltaTime)
{

}

void Game::render()
{

}

void Game::exit()
{
	// safe shutdown implementation here
	m_window->close();
}

// revisit, does weird things to shapes/sprites
void Game::resizeWindow(int width, int height)
{
	float newRatio = static_cast<float>(width) / static_cast<float>(height);

	if (abs(newRatio - m_aspectRatio) < 0.05f)
		return;

	float newWidth = 1.f;
	float newHeight = 1.f;
	float newViewX = 0.f;
	float newViewY = 0.f;

	if (m_aspectRatio > newRatio)
	{
		newHeight = newRatio / m_aspectRatio;
		newViewY = (1.f - newHeight) / 2.f;
	}
	else
	{
		newWidth = m_aspectRatio / newRatio;
		newViewX = (1.f - newWidth) / 2.f;
	}

	sf::View view = m_window->getView();
	view.setViewport(sf::FloatRect({ newViewX, newViewY }, { newWidth, newHeight }));
	m_window->setView(view);
}
