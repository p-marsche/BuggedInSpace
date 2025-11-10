#include "ErrorWindow.hpp"	//< idk if we want/need that, but i put it in for now
#include "Game.hpp"
#include "pch.h"

int main()
{
	try
	{
		std::cout << "Press ESC key to close window" << std::endl;
		std::unique_ptr<Game> game = std::make_unique<Game>();
		game->run();
		std::cout << "All done" << std::endl;
	}
	catch (std::exception e)
	{
		ErrorWindow errorWindow = ErrorWindow(e.what());
		errorWindow.showError();
	}

	return 0; // only here to shut compiler up for now :D
};
