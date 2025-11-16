#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void run();
	void exit();
	void update(float deltaTime);
	void render();

private:
	const int WIDTH;
	const int HEIGHT;
	const std::string TITLE;
	sf::FloatRect m_viewBorder;
	sf::FloatRect m_worldBorder;
	sf::Vector2i m_cameraDeadzone;
	sf::Vector2f m_timerPosition;
	sf::Text m_victoryTime;
	int m_playerID;
	float m_aspectRatio;
	bool m_missionFinished;
	float m_totalTimeElapsed;
	std::string m_totalTime;
	sf::Clock m_clock;
	std::shared_ptr<sf::RenderWindow> m_window;

	void resizeWindow(int width, int height);
	void initialize();
	void handleEvents();
	void checkCameraDeadzone(sf::Vector2f playerPos);
	void createEntities();
	void convertTimeToString();
	void renderTimer(sf::Vector2f position);
};
