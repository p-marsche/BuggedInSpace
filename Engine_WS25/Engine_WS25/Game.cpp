#include "Game.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

Game::Game()
	: WIDTH(640)
	, HEIGHT(360)
	, ASPECTRATIO(WIDTH/HEIGHT)
	, TITLE("Engine_WS25")
	, m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE))
	, m_clock()
{
	m_window->setFramerateLimit(60);
}

void Game::Run()
{
	Initialize();
	float deltaTime = 0.f;

	while (m_window->isOpen())
	{
		HandleEvents();

		deltaTime = m_clock.restart().asSeconds();
		Update(deltaTime);
		Draw();
	}
}

void Game::Initialize()
{
	m_goToIndex.emplace("Player1", static_cast<int>(m_gameObjects.size()));
	m_gameObjects.emplace_back(GameObjectFactory::GetInstance().CreatePlayer(1));
	m_goToIndex.emplace("Player2", static_cast<int>(m_gameObjects.size()));
	m_gameObjects.emplace_back(GameObjectFactory::GetInstance().CreatePlayer(2));
}

void Game::HandleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				CloseGame();
				break;
			case sf::Event::Resized:
				ResizeWindow(event.size.width, event.size.height);
		}
	}
}

void Game::Update(float deltaTime)
{
	for (auto& go : m_gameObjects)
		go->Update(deltaTime);
}

void Game::Draw()
{
	m_window->clear(sf::Color::Black);

	for (auto& go : m_gameObjects)
		go->Draw(*m_window);

	m_window->display();
}

void Game::CloseGame()
{
	// safe shutdown implementation here
	m_window->close();
}

void Game::ResizeWindow(int width, int height)
{
	float newRatio = static_cast<float>(width / height);

	if (abs(newRatio - ASPECTRATIO) < 0.05f)
		return;

	float newWidth = 1.f;
	float newHeight = 1.f;
	float newViewX = 0.f;
	float newViewY = 0.f;

	if (ASPECTRATIO > newRatio)
	{
		newHeight = newRatio / ASPECTRATIO;
		newViewY = (1.f - newHeight) / 2.f;
	}
	else
	{
		newWidth = ASPECTRATIO / newRatio;
		newViewX = (1.f - newWidth) / 2.f;
	}

	sf::View view = m_window->getView();
	view.setViewport(sf::FloatRect({ newViewX, newViewY }, { newWidth, newHeight }));
	m_window->setView(view);
}