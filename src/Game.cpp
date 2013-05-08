#include <Game.hpp>
#include <SFML/OpenGL.hpp>
#include <GameplayState.hpp>

Game::Game(const GameSettings& inSettings)
	: settings(inSettings), stateManager(inSettings), quitting(false)
{
}

Game::~Game()
{
}

void Game::Run()
{
	// Add the starting state.
	GameplayState* gstate = new GameplayState();
	stateManager.AddState(gstate);

	// Create the main window and activate the context.
	mainWindow.create(settings.windowSettings, settings.title);
	mainWindow.setFramerateLimit(0);
	mainWindow.setActive();

	// Setup the timing.
	float ticks = 1000.0f / (float)settings.framerate;
	int loops = 0;
	float interpolation = 0.0f, nextTick = 0.0f;
	sf::Clock gameClock;

	// Game Loop
	while(!quitting)
	{
		// The time elapsed since the start of the game.
		unsigned int timeElapsed = gameClock.getElapsedTime().asMilliseconds();

		// Update at a fixed rate.
		loops = 0;
		while(timeElapsed > nextTick && loops < settings.frameskip)
		{
			Update(timeElapsed);

			nextTick += ticks;
			loops++;
		}

		// Draw the scene and pass it a delta value to perform proper interpolation.
		interpolation = static_cast<float>(timeElapsed + ticks - nextTick) / static_cast<float>(ticks);
		Draw(interpolation);
	}
}

void Game::Update(unsigned int timestep)
{
	stateManager.Update(timestep);

	sf::Event ev;
	while(mainWindow.pollEvent(ev))
	{
		if(ev.type == sf::Event::Closed)
			quitting = true;
	}
}

void Game::Draw(float delta)
{
	mainWindow.clear();
	stateManager.Draw(delta);
	mainWindow.display();
}