#include "pch.h"

#include "ErrorWindow.hpp"	//< idk if we want/need that, but i put it in for now
#include "Game.hpp"
#include "GameState.hpp"
#include "GameStateManager.hpp"
#include "InputManager.hpp"
#include "TestMenu.hpp"

GameStateManager gameStateManager;

int main()
{
	try
	{
		Game game = Game();
		game.run();
	}
	catch (std::exception e)
	{
		ErrorWindow errorWindow = ErrorWindow(e.what());
		errorWindow.showError();
	}
};
