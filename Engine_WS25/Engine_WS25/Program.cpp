#include "Game.h"
#include <iostream>
#include <memory>

static int Main()
{
	std::cout << "Press ESC key to close window" << std::endl;
	std::unique_ptr<Game> game = std::make_unique<Game>();
	std::cout << "All done" << std::endl;
	return 0; // only here to shut compiler up for now :D
};
