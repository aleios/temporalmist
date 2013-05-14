#include <Game.hpp>
#include <GL/glew.h>
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
	// Create the main window and activate the context.
	mainWindow.create(settings.windowSettings, settings.title, 7U, sf::ContextSettings(0, 0, 0, 4, 3));
	mainWindow.setFramerateLimit(0);
	mainWindow.setActive();

	// Disable depth and enable texturing and alpha blending.
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set the clear color.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Get the OpenGL version.
	int min = 0, maj = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &maj);
	glGetIntegerv(GL_MINOR_VERSION, &min);

	std::cout << "GL Version: " << maj << "." << min << "\n";

	// Initialize GLEW with experimental functions.
	glewExperimental = GL_TRUE;
	GLenum glewOK = glewInit();

	if(glewOK == GLEW_OK)
	{
		std::cout << "GLEW " << glewGetString(GLEW_VERSION) << " initialized successfully.\n";
	}
	else
	{
		std::cout << "GLEW encountered an error.\n";
	}

	// Add the starting state.
	GameplayState* gstate = new GameplayState();
	stateManager.AddState(gstate);

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

		stateManager.OnEvent(ev);
	}
}

void Game::Draw(float delta)
{
	glClear(GL_COLOR_BUFFER_BIT);
	stateManager.Draw(delta);
	mainWindow.display();
}