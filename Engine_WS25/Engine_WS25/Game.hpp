#pragma once

#include "GameState.hpp"

class GameObject;

class Game : public GameState
{
public:
	Game();
	virtual void run() override;
	virtual void exit() override;
	virtual void update(float deltaTime) override;
	virtual void render() override;

private:
	const int WIDTH;
	const int HEIGHT;
	const std::string TITLE;
	float m_aspectRatio;
	float m_cameraScrollTime, m_maxScrollTime;
	int m_projectileCount;
	sf::Clock m_clock;
	std::unique_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<GameObject> m_background;
	std::unordered_map<std::string, std::shared_ptr<GameObject> > m_gameObjects;

	void resizeWindow(int width, int height);
	void initialize();
	void handleEvents();
	void removeGameObject(std::string name);
	void moveCamera();
	void keepObjectInView(std::string key, sf::Vector2f topLeft, sf::Vector2f size);
	void checkPlayerShooting(int playerNumber);
};
