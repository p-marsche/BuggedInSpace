#include "Game.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "InputManager.h"

Game::Game()
	: WIDTH(1280)
	, HEIGHT(720)
	, TITLE("Engine_WS25")
	, m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE))
	, m_clock()
{
	m_window->setFramerateLimit(60);
	m_window->setKeyRepeatEnabled(false);
	m_aspectRatio = static_cast<float>(WIDTH / HEIGHT);
}

void Game::Run()
{
	Initialize();
	float deltaTime = 0.f;

	while (m_window->isOpen())
	{
		InputManager::GetInstance().Update();
		HandleEvents();

		deltaTime = m_clock.restart().asSeconds();
		Update(deltaTime);
		Draw();
	}
}

void Game::Initialize()
{
	InputManager::GetInstance().Init();

	m_goToIndex.emplace("Player1", static_cast<int>(m_gameObjects.size()));
	m_gameObjects.emplace_back(GameObjectFactory::GetInstance().CreatePlayer(1));

	/*m_goToIndex.emplace("Player2", static_cast<int>(m_gameObjects.size()));
	m_gameObjects.emplace_back(GameObjectFactory::GetInstance().CreatePlayer(2));*/
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
				break;
			case sf::Event::KeyPressed:
				InputManager::GetInstance().OnKeyPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				InputManager::GetInstance().OnKeyReleased(event.key.code);
				break;
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

void Game::RemoveGameObject(std::string name)
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