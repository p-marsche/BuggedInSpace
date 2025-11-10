#pragma once

#include "pch.h"

#include "GameStateManager.hpp"

class GameState
{
public:
	virtual void init(GameStateManager* manager);
	virtual void exit() = 0;
	virtual void update(float delta) = 0;
	virtual void render() = 0;

private:
	GameStateManager& m_manager;
};
