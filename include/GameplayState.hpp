#ifndef GAMEPLAYSTATE_HPP
#define GAMEPLAYSTATE_HPP

#include <GameState.hpp>

#include <Camera.hpp>
#include <Shader.hpp>
#include <Player.hpp>

class GameplayState
	: public GameState
{
public:
	GameplayState();
	~GameplayState();

	void OnCreate(const GameSettings& inSettings);
	void Update(unsigned int timestep);
	void Draw(float delta);
	void OnDestroy();
private:
	Camera mainCamera;
	Matrix projectionMatrix;
	Shader basicShader;

	Player player;
};

#endif