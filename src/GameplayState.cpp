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

sf::Texture tex;
Map map;

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
	basicShader.Load("assets/shaders/basic.vert", "assets/shaders/basic.frag");
	basicShader.Bind();
	basicShader.SetParameter("projectionMatrix", &projectionMatrix[0][0]);

	// Load the texture shader.
	textureShader.Load("assets/shaders/textured.vert", "assets/shaders/textured.frag");
	textureShader.Bind();
	textureShader.SetParameter("projectionMatrix", &projectionMatrix[0][0]);

	// Setup the player with their texture.
	tex.loadFromFile("assets/textures/player.png");
	
	int texWidth = (tex.getSize().x / 2);
	int texHeight = (tex.getSize().y / 2);

	// TODO: Replace this with an actual level manager system.
	map.Load("assets/maps/test.tmx");

	std::vector<Vertex> verts;
	Vertex v;

	v.pos = Vector3(-texWidth, -texHeight, 0);
	v.col = Color(255, 255, 255, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(0, 0);
	verts.push_back(v);

	v.pos = Vector3(texWidth, -texHeight, 0);
	v.col = Color(255, 255, 255, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(1, 0);
	verts.push_back(v);

	v.pos = Vector3(texWidth, texHeight, 0);
	v.col = Color(255, 255, 255, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(1, 1);
	verts.push_back(v);

	v.pos = Vector3(-texWidth, texHeight, 0);
	v.col = Color(255, 255, 255, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(0, 1);
	verts.push_back(v);

	// Part 2
	v.pos = Vector3(-texWidth + (texWidth * 2), -texHeight, 0);
	v.col = Color(255, 0, 0, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(0, 0);
	verts.push_back(v);

	v.pos = Vector3(texWidth + (texWidth * 2), -texHeight, 0);
	v.col = Color(255, 0, 0, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(1, 0);
	verts.push_back(v);

	v.pos = Vector3(texWidth + (texWidth * 2), texHeight, 0);
	v.col = Color(255, 0, 0, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(1, 1);
	verts.push_back(v);

	v.pos = Vector3(-texWidth + (texWidth * 2), texHeight, 0);
	v.col = Color(255, 0, 0, 255);
	v.normal = Vector3(1, 1, 1);
	v.texcoords = Vector2(0, 1);
	verts.push_back(v);

	vbo.SetData(verts);

	std::vector<unsigned short> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	indices.push_back(0); indices.push_back(3); indices.push_back(2);

	indices.push_back(4); indices.push_back(5); indices.push_back(6);
	indices.push_back(4); indices.push_back(7); indices.push_back(6);
	ibo.SetData(indices);
}

void GameplayState::OnEvent(const sf::Event& ev)
{
}

void GameplayState::Update(unsigned int timestep)
{
	// TODO: Make the player speed, gravity, etc. into proper constants.
	// Update player logic, sounds, etc.
	player.SetVelocity(Vector2(0, 0));
	Vector2 playerVelocity = player.GetVelocity();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		playerVelocity.x = 10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		playerVelocity.x = -10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		playerVelocity.y = -10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		playerVelocity.y = 10;

	// Effect the player velocity by gravity.
	//playerVelocity.y -= 0.2f;

	// Set the velocity and position.
	player.SetVelocity(playerVelocity, false);
	player.SetPosition(playerVelocity, true);

	mainCamera.SetPosition(Vector2(player.GetPosition().x - (settings.windowSettings.width / 2.0f), player.GetPosition().y - (settings.windowSettings.height / 2.0f)));

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
	
	Matrix modelMatrix = Matrix::CreateIdentity() * Matrix::CreateTranslation(64, 64, 0);
	basicShader.SetParameter("modelMatrix", &modelMatrix[0][0]);
	map.DrawLayer(0);
	map.DrawLayer(1);

	basicShader.Unbind();

	textureShader.Bind();
	textureShader.SetParameter("viewMatrix", &viewMatrix[0][0]);

	sf::Texture::bind(&tex);
	Vector2 pos = player.GetPosition();
	Matrix playerMatrix = Matrix::CreateIdentity() * Matrix::CreateTranslation(pos.x, pos.y, 0);
	textureShader.SetParameter("modelMatrix", &playerMatrix[0][0]);
	

	// TEST
	vbo.Bind();
	ibo.Bind();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (GLvoid*)(6 * sizeof(unsigned short)));

	vbo.Unbind();

	// END TEST

	textureShader.Unbind();

	/*
	Matrix otherMatrix = Matrix::CreateIdentity() * Matrix::CreateTranslation(40, 40, 0);
	basicShader.SetParameter("modelMatrix", &otherMatrix[0][0]);
	vbo.DrawIndexed(ibo);*/

	//Matrix mapMatrix = Matrix::CreateIdentity() * Matrix::CreateTranslation(10, 10, 0);
	//basicShader.SetParameter("modelMatrix", &mapMatrix[0][0]);
	//map.Draw();

	// Unbind the shader.
}

void GameplayState::OnDestroy()
{
	// Unload assets.
}