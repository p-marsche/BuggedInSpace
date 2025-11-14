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
		//InputManager::getInstance().init();

		std::cout << "Press ESC key to close window" << std::endl;
		// disabled for now cause causes memory leak
		/*gameStateManager.registerState(GameStateEnum::Game, new Game());
		gameStateManager.registerState(GameStateEnum::Menu, new TestMenu());
		gameStateManager.setState(GameStateEnum::Menu);*/
		//instead just run Game
		Game game = Game();
		game.run();
		std::cout << "All done" << std::endl;
	}
	catch (std::exception e)
	{
		ErrorWindow errorWindow = ErrorWindow(e.what());
		errorWindow.showError();
	}

	return 0; // only here to shut compiler up for now :D
};
