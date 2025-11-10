#include "pch.h"

#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

Game::Game()
	: WIDTH(1280)
	, HEIGHT(720)
	, TITLE("Engine_WS25")
	, m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE))
	, m_clock()
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
		draw();
	}
}

void Game::initialize()
{
	InputManager::getInstance().init();

	m_goToIndex.emplace("Player1", static_cast<int>(m_gameObjects.size()));
	m_gameObjects.emplace_back(GameObjectFactory::getInstance().createPlayer(1));

	/*m_goToIndex.emplace("Player2", static_cast<int>(m_gameObjects.size()));
	m_gameObjects.emplace_back(GameObjectFactory::GetInstance().CreatePlayer(2));*/
}

void Game::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				closeGame();
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
	for (auto& go : m_gameObjects)
		go->update(deltaTime);
}

void Game::draw()
{
	m_window->clear(sf::Color::Black);

	for (auto& go : m_gameObjects)
		go->draw(*m_window);

	m_window->display();
}

void Game::closeGame()
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

void Game::removeGameObject(std::string name)
{
	auto res = m_goToIndex.find(name);
	if (res == m_goToIndex.end())
		return;

	// replace found object with last object in vec, then remove last object
	m_gameObjects.at(res->second) = m_gameObjects.back();
	m_gameObjects.pop_back();
	

	// find former last object, change its index(=value) to the new index(=value of searched object)
	for (auto& [key, val] : m_goToIndex)
	{
		if (val == m_gameObjects.size())
		{
			m_goToIndex.at(key) = res->second;
			m_goToIndex.erase(name);
			break;
		}
	}
}
