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
	float m_aspectRatio;
	float m_cameraScrollTime;
	const std::string TITLE = "Engine_WS25";
	sf::Clock m_clock;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<GameObject> m_background;
	std::vector<std::shared_ptr<GameObject> > m_gameObjects;
	// replace std::string with an enum of important go's (player(s), etc)?
	std::unordered_map<std::string, int> m_goToIndex;
	// ==> wouldn't it be better to just have important GOs as seperate references?
	// or could also get rid of the vector and just use a map with strings/enums as key and GO as value

	void closeGame();
	void resizeWindow(int width, int height);
	void initialize();
	void handleEvents();
	void update(float deltaTime);
	void draw();
	void removeGameObject(std::string name);
};
