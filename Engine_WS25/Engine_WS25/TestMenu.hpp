#pragma once

#include "GameState.hpp"

class TestMenu : public GameState
{
public:
	TestMenu();
	virtual void exit() override;
	virtual void render() override;
	virtual void run() override;
	virtual void update(float deltaTime) override;

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	void handleEvents();
};