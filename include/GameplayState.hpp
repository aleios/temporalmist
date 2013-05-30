#ifndef GAMEPLAYSTATE_HPP
#define GAMEPLAYSTATE_HPP

#include <GameState.hpp>

#include <Camera.hpp>
#include <Shader.hpp>
#include <Player.hpp>

#include <VertexBufferObject.hpp>
#include <IndexBufferObject.hpp>

class GameplayState
	: public GameState
{
public:
	GameplayState();
	~GameplayState();

	void OnCreate(const GameSettings& inSettings);
	void OnEvent(const sf::Event& ev);
	void Update(unsigned int timestep);
	void Draw(float delta);
	void OnDestroy();

	void AddGameObject(GameObject* inObj);
private:
	Camera mainCamera;
	Matrix projectionMatrix;
	GameSettings settings;

	std::vector<GameObject*> gameObjects;
};

#endif