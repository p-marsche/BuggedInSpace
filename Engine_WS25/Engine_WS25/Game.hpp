#pragma once

class GameObject;

class Game
{
public:
	Game();
	void run();

private:
	const int WIDTH;
	const int HEIGHT;
	const std::string TITLE = "Engine_WS25";
	float m_aspectRatio;
	float m_cameraScrollTime, m_maxScrollTime;
	int m_projectileCount;
	sf::Clock m_clock;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<GameObject> m_background;
	std::unordered_map<std::string, std::shared_ptr<GameObject> > m_gameObjects;

	void closeGame();
	void resizeWindow(int width, int height);
	void initialize();
	void handleEvents();
	void update(float deltaTime);
	void draw();
	void removeGameObject(std::string name);
	void moveCamera();
	void keepObjectInView(std::string key, sf::Vector2f topLeft, sf::Vector2f size);
};
