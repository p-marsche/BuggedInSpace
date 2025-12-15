#include "pch.h"

#include <random>

#include "AssetManager.hpp"
#include "MissionManager.hpp"
#include "InputManager.hpp"
#include "SystemManager.hpp"
#include "StatusComponent.hpp"
#include "Game.hpp"
#include "EntityFactory.hpp"
#include "Registry.hpp"
#include "VectorUtils.hpp"

Game::Game()
	: WIDTH(1920)
	, HEIGHT(1080)
	, TITLE("Engine_WS25")
	, m_cameraDeadzone(WIDTH/8, HEIGHT/8)
	, m_timerPosition(0, 0)
	, m_playerID(-1)
	, m_totalTime("")
	, m_victoryTime()
	, m_missionFinished(false)
	, m_totalTimeElapsed(0)
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

	createEntities();
	AssetManager::getInstance().loadFont("MainFont", "MainFont.ttf");

	m_victoryTime.setFont(AssetManager::getInstance().getFont("MainFont"));
	m_victoryTime.setCharacterSize(50);
	m_victoryTime.setFillColor(sf::Color::Red);
	m_victoryTime.setOutlineColor(sf::Color::White);
	m_victoryTime.setOutlineThickness(3.f);
	auto tempVec =
		sf::Vector2f(m_victoryTime.getGlobalBounds().width / 2.f,
			m_victoryTime.getGlobalBounds().height / 2.f);
	m_victoryTime.setOrigin(tempVec);

	SystemManager::getInstance().init();
	int missionThreshold = 0;
	auto tmp =
		std::dynamic_pointer_cast<ComponentBlock<StatusComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Status))
		->m_components;
	for (auto& comp : tmp)
		if (comp.m_tag == "Empty")
			missionThreshold++;

	MissionManager::getInstance().init(missionThreshold);
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
				if (event.key.code == sf::Keyboard::Key::Escape && m_missionFinished)
					exit();
				break;
			case sf::Event::KeyReleased:
				InputManager::getInstance().onKeyReleased(event.key.code);
				break;
		}
	}
}

void Game::update(float deltaTime)
{
	m_missionFinished = MissionManager::getInstance().checkMission();
	if (!m_missionFinished)
	{
		m_totalTimeElapsed += deltaTime;
		convertTimeToString();
	}

	SystemManager::getInstance().update(deltaTime);
	Registry::getInstance().update();
	sf::Vector2f playerPos = Registry::getInstance().getPlayerPosition(m_playerID);
	checkCameraDeadzone(playerPos);
}

void Game::render()
{
	m_window->clear(sf::Color::Black);
	SystemManager::getInstance().render(*m_window);

	m_timerPosition = m_window->getView().getCenter();
	if (m_missionFinished)
	{
		m_victoryTime.setCharacterSize(100);
		auto tempVec =
			sf::Vector2f(m_victoryTime.getGlobalBounds().width / 2.f,
				m_victoryTime.getGlobalBounds().height / 2.f);
		m_victoryTime.setOrigin(tempVec);
	}
	else
	{
		m_timerPosition +=
			sf::Vector2f(m_window->getView().getSize().x / 3.2,
				m_window->getView().getSize().y / 2.5);
	}


	renderTimer(m_timerPosition);

	m_window->display();
}

void Game::exit()
{
	// safe shutdown implementation here
	m_window->close();
}

void Game::convertTimeToString()
{
	int secs, mins, hours, tmp;
	tmp = static_cast<int>(m_totalTimeElapsed);
	hours = tmp / 3600;
	tmp -= 3600 * hours;
	mins = tmp / 60;
	secs = tmp - 60 * mins;

	std::stringstream temp;
	temp << std::setw(2) << std::setfill('0') << hours << " : "
		<< std::setw(2) << std::setfill('0') << mins << " : "
		<< std::setw(2) << std::setfill('0') << secs;

	m_totalTime = temp.str();
}

void Game::renderTimer(sf::Vector2f position)
{
	m_victoryTime.setString(m_totalTime);
	m_victoryTime.setPosition(position);
	m_window->draw(m_victoryTime);
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
	float centerDistX = std::abs(centerDist.x);
	float centerDistY = std::abs(centerDist.y);

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

void Game::createEntities()
{
	AssetManager::getInstance().loadTexture("Player", "Player_Ship1.png");
	AssetManager::getInstance().loadTexture("Background", "Background.png");
	AssetManager::getInstance().loadTexture("Filled", "Filled_Console.png");
	AssetManager::getInstance().loadTexture("Empty", "Empty_Console.png");
	AssetManager::getInstance().loadTexture("String", "String.png");

	auto inputMap = std::unordered_map<InputEnum, sf::Keyboard::Key>();
	inputMap.emplace(InputEnum::Left, sf::Keyboard::Key::Left);
	inputMap.emplace(InputEnum::Right, sf::Keyboard::Key::Right);
	inputMap.emplace(InputEnum::Up, sf::Keyboard::Key::Up);

	int bgID = EntityFactory::getInstance().createBackground(sf::Vector2f(0.f, 0.f),
		sf::Vector2f(4.f, 4.f), "Background");

	m_playerID =
		EntityFactory::getInstance().createPlayer(sf::Vector2f(0.f, 0.f),
			sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Player", 0.8f, 200.f,
			inputMap);

	std::random_device gen;
	int rng = gen();
	if (rng < 0)
		rng = abs(rng);
	if (rng == 0)
		rng = 1;
	int choice = rng % 3;
	std::cout << choice << std::endl;
		switch (choice)
		{
			case 0:
				entitySetup1();
				break;
			case 1:
				entitySetup2();
				break;
			case 2:
				entitySetup3();
				break;
			default:
				entitySetup1();
				break;
		}
}

void Game::entitySetup1()
{
	EntityFactory::getInstance().createEmptyConsole(sf::Vector2f(-300.f, 100.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Empty", 1.2f);
	EntityFactory::getInstance().createEmptyConsole(sf::Vector2f(1000.f, -1100.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Empty", 1.2f);

	EntityFactory::getInstance().createString(sf::Vector2f(-1300.f, 900.f),
		sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.f), "String", 1.1f);
	EntityFactory::getInstance().createString(sf::Vector2f(2100.f, 700.f),
		sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.f), "String", 1.1f);

	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(800.f, -700.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(1200.f, 0.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(700.f, 800.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
}

void Game::entitySetup2()
{
	EntityFactory::getInstance().createEmptyConsole(sf::Vector2f(-800.f, 100.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Empty", 1.2f);
	EntityFactory::getInstance().createEmptyConsole(sf::Vector2f(1000.f, -1400.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Empty", 1.2f);

	EntityFactory::getInstance().createString(sf::Vector2f(-800.f, 1300.f),
		sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.f), "String", 1.1f);
	EntityFactory::getInstance().createString(sf::Vector2f(1800.f, -1300.f),
		sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.f), "String", 1.1f);

	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(800.f, -1700.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(1200.f, 0.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(1700.f, 800.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
}

void Game::entitySetup3()
{
	EntityFactory::getInstance().createEmptyConsole(sf::Vector2f(-1800.f, 600.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Empty", 1.2f);
	EntityFactory::getInstance().createEmptyConsole(sf::Vector2f(1000.f, -1200.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Empty", 1.2f);

	EntityFactory::getInstance().createString(sf::Vector2f(-800.f, 1300.f),
		sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.f), "String", 1.1f);
	EntityFactory::getInstance().createString(sf::Vector2f(1800.f, -1300.f),
		sf::Vector2f(3.f, 3.f), sf::Vector2f(1.f, 0.f), "String", 1.1f);

	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(800.f, -1700.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(-1200.f, 300.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
	EntityFactory::getInstance().createFilledConsole(sf::Vector2f(1700.f, 800.f),
		sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), "Filled");
}