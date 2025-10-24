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
	void Initialize();
	void HandleEvents();
	void Update(float deltaTime);
	void Draw();

	const int WIDTH = 640;
	const int HEIGHT = 360;
	const std::string TITLE = "Engine_WS25";
	sf::Clock clock;
	std::unique_ptr<sf::VideoMode> mode = std::make_unique<sf::VideoMode>(WIDTH, HEIGHT);
	std::shared_ptr<sf::RenderWindow> window;
	std::vector<std::shared_ptr<GameObject> > gameObjects;
	// replace std::string with an enum of important go's (player(s), etc)
	std::unordered_map<std::string, int> goToIndex;
};

