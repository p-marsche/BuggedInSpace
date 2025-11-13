#pragma once

#include "GameStateEnum.hpp"

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	void setState(GameStateEnum name);
	void registerState(GameStateEnum name, GameState* state);

private:
	std::map<GameStateEnum, GameState*> m_states;
	GameState* m_currentState;
};
