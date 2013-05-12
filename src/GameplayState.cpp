#include <GameplayState.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <Map.hpp>

GameplayState::GameplayState()
{
}

GameplayState::~GameplayState()
{
}

void GameplayState::OnCreate(const GameSettings& inSettings)
{
	// Setup the main camera.
	mainCamera.SetPosition(Vector2(0, 0));
	mainCamera.SetRotation(0);

	// Setup the projection matrix and the viewport.
	glViewport(0, 0, inSettings.windowSettings.width, inSettings.windowSettings.height);
	projectionMatrix = Matrix::CreateIdentity() * Matrix::OrthoProjection(0, inSettings.windowSettings.width, inSettings.windowSettings.height, 0, -1, 1);

	// Load the basic shader.
	basicShader.Load("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	basicShader.Bind();
	basicShader.SetParameter("projectionMatrix", &projectionMatrix[0][0]);

	// Setup the player with their texture.
	sf::Texture tex;
	tex.loadFromFile("assets/textures/player.png");


	// TODO: Replace this with an actual level manager system.
	Map map("assets/maps/testx.tmx");

}

void GameplayState::OnEvent(const sf::Event& ev)
{
}

void GameplayState::Update(unsigned int timestep)
{
	// TODO: Make the player speed, gravity, etc. into proper constants.
	// Update player logic, sounds, etc.
	Vector2 playerVelocity = player.GetVelocity();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		playerVelocity.x = 1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		playerVelocity.x = -1;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		playerVelocity.y = -10;

	// Effect the player velocity by gravity.
	playerVelocity.y += 0.2f;

	// Set the velocity and position.
	player.SetVelocity(playerVelocity, false);
	player.SetPosition(playerVelocity, true);

	// Update the camera to the proper view matrix.
	mainCamera.Update();
}

void GameplayState::Draw(float delta)
{
	// Bind the shader.
	basicShader.Bind();

	// Draw vertices to screen.
	Matrix viewMatrix = mainCamera.GetCameraMatrix();
	basicShader.SetParameter("viewMatrix", &viewMatrix[0][0]);

	// Unbind the shader.
	basicShader.Unbind();

}

void GameplayState::OnDestroy()
{
	// Unload assets.
}