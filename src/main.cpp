#include <iostream>
#include <Game.hpp>

int main(int argc, char** argv)
{
	Game game(GameSettings(sf::VideoMode(800, 600, 32), "Temporal Mist"));
	
	game.Run();

	return 0;
}