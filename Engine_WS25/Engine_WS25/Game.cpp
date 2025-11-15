#include "pch.h"

#include "AssetManager.hpp"
#include "InputManager.hpp"
#include "SystemManager.hpp"
#include "Game.hpp"
#include "EntityFactory.hpp"
#include "Registry.hpp"
#include "VectorUtils.hpp"

Game::Game()
	: WIDTH(1920)
	, HEIGHT(1080)
	, TITLE("Engine_WS25")
	, m_cameraDeadzone(WIDTH/8, HEIGHT/8)
	, m_playerID(-1)
{
	m_clock = sf::Clock();
	m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE);
	m_window->setFramerateLimit(60);
	m_window->setKeyRepeatEnabled(false);
	m_aspectRatio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
	m_viewBorder = sf::FloatRect(sf::Vector2f(0.f, 0.f),
		sf::Vector2f(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)));
	m_worldBorder = sf::FloatRect(sf::Vector2f(0.f, 0.f),
		sf::Vector2f(4.f * static_cast<float>(WIDTH), 4.f * static_cast<float>(HEIGHT)));
	m_window->setView(sf::View(m_viewBorder));
}

void Game::run()
{
	initialize();
	float deltaTime = 0.f;

	while (m_window->isOpen())
	{
		handleEvents();

		deltaTime = m_clock.restart().asSeconds();
		update(deltaTime);
		render();
		InputManager::getInstance().clearKeyPressed();
	}
}

void Game::initialize()
{
	InputManager::getInstance().init();
	Registry::getInstance().init(100);

	AssetManager::getInstance().loadTexture("Player", "Player_Ship1.png");
	AssetManager::getInstance().loadTexture("Background", "Background.png");
	AssetManager::getInstance().loadTexture("Enemy", "Enemy_Ship1.png");

	auto inputMap = std::unordered_map<InputEnum, sf::Keyboard::Key>();
	inputMap.emplace(InputEnum::Left, sf::Keyboard::Key::Left);
	inputMap.emplace(InputEnum::Right, sf::Keyboard::Key::Right);
	inputMap.emplace(InputEnum::Up, sf::Keyboard::Key::Up);

	m_playerID = 
		EntityFactory::getInstance().createPlayer(sf::Vector2f(0.f, 0.f), 
		sf::Vector2f(1.f, 1.f),sf::Vector2f(1.f, 0.f), "Player", 0.8f, 200.f,
		inputMap);

	int bgID = EntityFactory::getInstance().createBackground(sf::Vector2f(0.f, 0.f),
		sf::Vector2f(12.f, 16.f), "Background");

	int opID = EntityFactory::getInstance().createObstacle(sf::Vector2f(250.f, 250.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Enemy", 0.8f);

	std::cout << "PlayerID: " << m_playerID << std::endl;
	std::cout << "bgID: " << bgID << std::endl;
	std::cout << "opID: " << opID << std::endl;

	SystemManager::getInstance().init();
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
	SystemManager::getInstance().update(deltaTime);
	Registry::getInstance().update();

	sf::Vector2f playerPos = Registry::getInstance().getPlayerPosition(m_playerID);
	checkCameraDeadzone(playerPos);
}

void Game::render()
{
	m_window->clear(sf::Color::Black);

	SystemManager::getInstance().render(*m_window);

	m_window->display();
}

void Game::exit()
{
	// safe shutdown implementation here
	m_window->close();
}

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

void Game::checkCameraDeadzone(sf::Vector2f playerPosition)
{
	auto centerDist = playerPosition - m_window->getView().getCenter();
	auto offset = sf::Vector2f(centerDist);
	int centerDistX = std::abs(centerDist.x);
	int centerDistY = std::abs(centerDist.y);

	if (centerDistX <= m_cameraDeadzone.x && centerDistY <= m_cameraDeadzone.y)
		return;

	if (centerDistX > m_cameraDeadzone.x)
		offset.x +=
		(centerDist.x > 0) ? ((-1.f) * m_cameraDeadzone.x) : m_cameraDeadzone.x;
	else
		offset.x = 0.f;

	if (centerDistY > m_cameraDeadzone.y)
		offset.y +=
		(centerDist.y > 0) ? ((-1.f) * m_cameraDeadzone.y) : m_cameraDeadzone.y;
	else
		offset.y = 0.f;

	auto newView = m_window->getView();
	newView.move(offset);
	m_window->setView(newView);
}
