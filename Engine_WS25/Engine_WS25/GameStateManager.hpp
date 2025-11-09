#pragma once
#include <map>
#include <string>

class GameState;

class GameStateManager
{
private:
	std::map<std::string, GameState*> states;
	GameState* currentState;

public:
	GameStateManager() : currentState(nullptr) {}
	void setState(std::string name);
	void registerState(std::string name, GameState* state);
};
