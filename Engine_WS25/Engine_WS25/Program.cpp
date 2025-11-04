#include "Game.h"
#include <iostream>
#include <memory>
#include "ErrorWindow.h"	//< idk if we want/need that, but i put it in for now

int main()
{
	try
	{
		std::cout << "Press ESC key to close window" << std::endl;
		std::unique_ptr<Game> game = std::make_unique<Game>();
		game->Run();
		std::cout << "All done" << std::endl;
	}
	catch (std::exception e)
	{
		ErrorWindow errorWindow = ErrorWindow(e.what());
		errorWindow.showError();
	}

	return 0; // only here to shut compiler up for now :D
};
