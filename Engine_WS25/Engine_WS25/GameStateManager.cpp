#include "GameStateManager.hpp"
#include "GameState.hpp"

void GameStateManager::setState(std::string name)
{
	if (states.find(name) != states.end())	// check if state exists
	{
		GameState* state = states[name];
		if (state != currentState)
			currentState->exit();
		currentState = state;
		currentState->init(this);
	}
}

void GameStateManager::registerState(std::string name, GameState* state)
{
	if(states.find(name) == states.end())
		states.emplace(name, state);
}
