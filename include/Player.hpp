#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>

#include <GameObject.hpp>

#include <VertexBufferObject.hpp>
#include <IndexBufferObject.hpp>

class Player : 
	public GameObject
{
public:
	Player();
	~Player();

	void Draw();
	void Update(unsigned int timestep);

private:
	unsigned int state;
};

#endif