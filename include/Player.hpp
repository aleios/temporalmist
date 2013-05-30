#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>

#include <GameObject.hpp>

#include <VertexBufferObject.hpp>
#include <IndexBufferObject.hpp>

enum class PlayerState 
{
	IDLE,
	WALKLEFT,
	WALKRIGHT,
	JUMP,
	FALLING
};

class Player : 
	public GameObject
{
public:
	Player(const std::string& inTexFilename, const std::string& inAnimFilename = "");
	~Player();

	void Draw();
	void Update(unsigned int timestep);
private:
	PlayerState state;
};

#endif