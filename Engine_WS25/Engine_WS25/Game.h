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
	void run();

private:
	void closeGame();
	void resizeWindow(int width, int height);
	void initialize();
	void handleEvents();
	void update(float deltaTime);
	void draw();
	void removeGameObject(std::string name);


	const int WIDTH;
	const int HEIGHT;
	float m_aspectRatio;
	const std::string TITLE = "Engine_WS25";
	sf::Clock m_clock;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<std::shared_ptr<GameObject> > m_gameObjects;
	// replace std::string with an enum of important go's (player(s), etc)?
	std::unordered_map<std::string, int> m_goToIndex;
	// ==> wouldn't it be better to just have important GOs as seperate references?
	// or could also get rid of the vector and just use a map with strings/enums as key and GO as value
};
