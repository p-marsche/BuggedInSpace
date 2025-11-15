#include "pch.h"

#include "ErrorWindow.hpp"	//< idk if we want/need that, but i put it in for now
#include "Game.hpp"

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
