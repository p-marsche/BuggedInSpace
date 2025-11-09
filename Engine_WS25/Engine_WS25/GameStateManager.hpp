#pragma once
#include <map>
#include <string>

class GameState;

class GameStateManager
{
public:
	GameStateManager() : currentState(nullptr) {}
	void setState(std::string name);
	void registerState(std::string name, GameState* state);

private:
	std::map<std::string, GameState*> states;
	GameState* currentState;
};
