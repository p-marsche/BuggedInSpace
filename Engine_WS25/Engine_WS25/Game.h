#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameObject.h"

class Game
{
public:
	Game();
	void Run();

private:
	void CloseGame();
	void ResizeWindow(int width, int height);
	void Initialize();
	void HandleEvents();
	void Update(float deltaTime);
	void Draw();
	void RemoveGameObject(std::string name);


	const int WIDTH;
	const int HEIGHT;
	float m_aspectRatio;
	const std::string TITLE = "Engine_WS25";
	sf::Clock m_clock;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::shared_ptr<GameObject> > m_gameObjects;
	// replace std::string with an enum of important go's (player(s), etc)?
	std::unordered_map<std::string, int> m_goToIndex;
};

