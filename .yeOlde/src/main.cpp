#include "game.hpp"
#include <iostream>


int main()
{
	Engine::Game game(0); //(fullscreen, title, width, height) //if no parameters are passed, defaults as specified in definitions are set
	game.Run();

	return 0;
}
