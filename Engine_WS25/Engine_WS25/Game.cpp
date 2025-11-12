#include "pch.h"

#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "GameObjectManager.hpp"
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
		draw();
	}
}

void Game::initialize()
{
	InputManager::getInstance().init();
	GameObjectManager::getInstance().init();

	m_background = GameObjectFactory::getInstance().createBackground(sf::Vector2f(2.f, 3.f));

	m_gameObjects.emplace("Player1", GameObjectFactory::getInstance().createPlayer(1));
	m_gameObjects.emplace("Player2", GameObjectFactory::getInstance().createPlayer(2));

	m_gameObjects["Player1"]->moveObject(sf::Vector2f(200, 200));
	m_gameObjects["Player2"]->moveObject(sf::Vector2f(400, 400));

	GameObjectManager::getInstance().registerPlayer("Player1", m_gameObjects["Player1"]);
	GameObjectManager::getInstance().registerPlayer("Player2", m_gameObjects["Player2"]);
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
	// move that to game-state
	m_cameraScrollTime += deltaTime;
	moveCamera();

	if (m_cameraScrollTime >= m_maxScrollTime + 3)
		m_cameraScrollTime = 0.f;

	float leftBorder = m_window->getView().getCenter().x - (m_window->getView().getSize().x / 2.f);
	float rightBorder = m_window->getView().getCenter().x + (m_window->getView().getSize().x / 2.f);
	float topBorder = m_window->getView().getCenter().y - (m_window->getView().getSize().y / 2.f);
	float bottomBorder = m_window->getView().getCenter().y + (m_window->getView().getSize().y / 2.f);
	sf::Vector2f viewSize(m_window->getView().getSize().x, m_window->getView().getSize().y);
	keepObjectInView("Player1", sf::Vector2f(leftBorder, topBorder), viewSize);
	keepObjectInView("Player2", sf::Vector2f(leftBorder, topBorder), viewSize);

	for (auto& [_, go] : m_gameObjects)
		go->update(deltaTime);

	if (m_projectileCount > 100)
		m_projectileCount = 0;

	//CheckProjectilesInView(rightBorder);
	GameObjectManager::getInstance().update(deltaTime);
	checkPlayerShooting(1);
	checkPlayerShooting(2);
}

void Game::draw()
{
	m_window->clear(sf::Color::Black);

	m_background->draw(*m_window);

	/*for (auto& [_, go] : m_gameObjects)
		go->draw(*m_window);*/

	m_gameObjects["Player1"]->draw(*m_window);
	m_gameObjects["Player2"]->draw(*m_window);

	GameObjectManager::getInstance().draw(*m_window);

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
	auto res = m_gameObjects.find(name);
	if (res == m_gameObjects.end())
		return;

	m_gameObjects.erase(name);
}

void Game::moveCamera()
{
	float bgWidth = m_background->getSprite()->getGlobalBounds().width;

	sf::Vector2f startPos(static_cast<float>(WIDTH) / 2.f, static_cast<float>(HEIGHT) / 2.f);
	sf::Vector2f endPos(bgWidth - static_cast<float>(WIDTH) / 2.f, static_cast<float>(HEIGHT) / 2.f);

	sf::Vector2f newViewCenter =
		VecUtils::lerp(startPos, endPos, m_cameraScrollTime / m_maxScrollTime);

	sf::View view = m_window->getView();
	if (m_maxScrollTime - m_cameraScrollTime >= 0.1f)
		view.setCenter(newViewCenter);
	else if (m_cameraScrollTime == 0)
		view.setCenter(startPos);

	m_window->setView(view);
}


// drags Gameobject along if camera would scroll past it
void Game::keepObjectInView(std::string key, sf::Vector2f topLeft, sf::Vector2f size)
{
	std::shared_ptr<GameObject> go = m_gameObjects[key];
	auto position = go->getObjectPosition();
	float width = go->getSprite()->getGlobalBounds().width / 2.f;
	float height = go->getSprite()->getGlobalBounds().height / 2.f;
	float xMove = 0;
	float yMove = 0;

	// set players back to start on background-looping
	if (m_cameraScrollTime == 0)
		if (key == "Player1" || key == "Player2")
		{
			go->moveObject(sf::Vector2f(-1 * (position.x - width), 0.f));
			return;
		}

	if (position.x - width <= topLeft.x)
		xMove = (topLeft.x - (position.x - width));
	else if (position.x >= topLeft.x + size.x + width)
		xMove = (topLeft.x + size.x - position.x) + width;

	if (position.y - height <= topLeft.y)
		yMove = (topLeft.y - (position.y - height));
	else if (position.y + height >= topLeft.y + size.y)
		yMove = (topLeft.y +size.y - (position.y + height));

	go->moveObject(sf::Vector2f(xMove, yMove));
}

void Game::checkPlayerShooting(int playerNumber)
{
	if (playerNumber != 1 && playerNumber != 2)
		return;

	std::string key = "Player" + std::to_string(playerNumber);
	if (m_gameObjects[key]->isShooting())
		GameObjectManager::getInstance().activateProjectile(playerNumber);
}
