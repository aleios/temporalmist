#include <GameplayState.hpp>
#include <SFML/OpenGL.hpp>

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

	basicShader.Bind();
	basicShader.SetParameter("projectionMatrix", &projectionMatrix[0][0]);

	// Setup the player with their texture.
	sf::Texture tex;
	tex.loadFromFile("player.png");

	
}

void GameplayState::Update(unsigned int timestep)
{
	// Update player logic, sounds, etc.

	// Update the camera to the proper view matrix.
	mainCamera.Update();
}

void GameplayState::Draw(float delta)
{
	// Draw vertices to screen.
	Matrix viewMatrix = mainCamera.GetCameraMatrix();
	basicShader.SetParameter("viewMatrix", &viewMatrix[0][0]);

}

void GameplayState::OnDestroy()
{
	// Unload assets.
}