#pragma once
#include "GameStateManager.h"

class GameState
{
private:
	GameStateManager& m_manager;

public:
	virtual void init(GameStateManager* manager);
	virtual void exit() = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;
};