#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <GameSettings.hpp>
#include <StateManager.hpp>

class Game
{
public:
	Game(const GameSettings& inSettings);
	~Game();

	void Run();
private:
	void Update(unsigned int timestep);
	void Draw(float delta);

private:
	GameSettings settings;
	sf::RenderWindow mainWindow;

	bool quitting;
	StateManager stateManager;
};

#endif