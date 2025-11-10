#pragma once

#include <memory>
#include "GameStateEnum.hpp"

class GameStateManager;

class GameState
{
public:
	GameState();
	virtual void changeState(GameStateEnum state) const;
	virtual void exit() = 0;
	virtual void init(GameStateManager* manager);
	virtual void render() = 0;
	virtual void run() = 0;
	virtual void update(float deltaTime) = 0;

private:
	GameStateManager* m_manager;
};
