#include <GameplayState.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <Map.hpp>
#include <ShaderFactory.hpp>
#include <LevelManager.hpp>

GameplayState::GameplayState()
{
}

GameplayState::~GameplayState()
{
}

sf::Texture tex;
Player* player;

void GameplayState::OnCreate(const GameSettings& inSettings)
{
	// Save the settings for later use.
	settings = inSettings;

	// Setup the main camera.
	mainCamera.SetPosition(Vector2(0, 0));
	mainCamera.SetRotation(0);

	// Setup the projection matrix and the viewport.
	glViewport(0, 0, inSettings.windowSettings.width, inSettings.windowSettings.height);
	projectionMatrix = Matrix::CreateIdentity() * Matrix::OrthoProjection(0, inSettings.windowSettings.width, inSettings.windowSettings.height, 0, -1, 1);

	// Load the basic shader.
	Shader *shader = ShaderFactory::Get("basic");
	shader->Bind();
	shader->SetParameter("projectionMatrix", &projectionMatrix[0][0]);
	shader->Unbind();

	// Load the texture shader.
	shader = ShaderFactory::Get("textured");
	shader->Bind();
	shader->SetParameter("projectionMatrix", &projectionMatrix[0][0]);
	shader->Unbind();

	// Setup the player with their texture.
	tex.loadFromFile("assets/textures/player.png");
	
	int texWidth = (tex.getSize().x / 2);
	int texHeight = (tex.getSize().y / 2);

	// Load Levels.
	LevelManager* levelManager = LevelManager::GetInstance();
	levelManager->LoadLevel("assets/maps/test.tmx");
	
	levelManager->SetLevel(0);

	// Setup the player.
	Player* player = new Player("assets/textures/player.png", "assets/animations/player.anim");
	gameObjects.push_back(player);
}

void GameplayState::OnEvent(const sf::Event& ev)
{
	if(ev.type == sf::Event::Resized)
	{
		// Change the projection matrix.
		projectionMatrix = Matrix::OrthoProjection(0, ev.size.width, ev.size.height, 0, -1, 1);

		// Update the shaders with the new projection matrix.
		Shader* shader = ShaderFactory::Get("basic");
		shader->Bind();
		shader->SetParameter("projectionMatrix", &projectionMatrix[0][0]);

		shader = ShaderFactory::Get("textured");
		shader->Bind();
		shader->SetParameter("projectionMatrix", &projectionMatrix[0][0]);
		shader->Unbind();

		// Set the viewport.
		glViewport(0, 0, ev.size.width, ev.size.height);

		// Put the new Width and Height into the settings.
		settings.windowSettings.width = ev.size.width;
		settings.windowSettings.height = ev.size.height;
	}
}

void GameplayState::Update(unsigned int timestep)
{
	// Update all Game Objects.
	auto it = gameObjects.begin(), ite = gameObjects.end();
	for(; it != ite; ++it)
	{
		(*it)->Update(timestep);
	}

	mainCamera.SetPosition(Vector2(gameObjects[0]->GetPosition().x - (settings.windowSettings.width / 2.0f), gameObjects[0]->GetPosition().y - (settings.windowSettings.height / 2.0f)));

	// Update the camera to the proper view matrix.
	mainCamera.Update();
}

void GameplayState::Draw(float delta)
{
	// Get the camera matrix.
	Matrix viewMatrix = mainCamera.GetCameraMatrix();

	// Draw all textured objects.
	Shader* shader = ShaderFactory::Get("textured");
	shader->Bind();
	shader->SetParameter("viewMatrix", &viewMatrix[0][0]);


	Map& map = LevelManager::GetInstance()->GetCurrentMap();
	Matrix modelMatrix = Matrix::CreateIdentity() * Matrix::CreateTranslation(0, 0, 0);
	shader->SetParameter("modelMatrix", &modelMatrix[0][0]);
	map.DrawLayer(0);
	map.DrawLayer(1);

	/*
	sf::Texture::bind(&tex);
	Matrix playerMatrix = gameObjects[0]->GetMatrix();
	shader->SetParameter("modelMatrix", &playerMatrix[0][0]);
	gameObjects[0]->Draw();
	*/

	// Draw all game objects.
	auto it = gameObjects.begin(), ite = gameObjects.end();
	for(; it != ite; ++it)
	{
		Matrix objMatrix = (*it)->GetMatrix();
		shader->SetParameter("modelMatrix", &objMatrix[0][0]);
		(*it)->Draw();
	}

	shader->Unbind();
}

void GameplayState::OnDestroy()
{
	// Remove all game objects and release memory.
	for(int i = 0; i < gameObjects.size(); i++)
	{
		if(gameObjects[i] != 0)
			delete gameObjects[i];
	}
	gameObjects.clear();
}

void GameplayState::AddGameObject(GameObject* inObj)
{
	if(inObj != 0)
		gameObjects.push_back(inObj);
}