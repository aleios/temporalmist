#include <Player.hpp>
#include <Matrix.hpp>

#include <SFML/Window/Event.hpp>

Player::Player()
{
	// Setup the player with their texture.
	//tex.loadFromFile("assets/textures/player.png");
}

Player::~Player()
{
}

void Player::Draw()
{
	// Bind the texture.
	vbo.DrawIndexed(ibo);
}

void Player::Update(unsigned int timestep)
{
	Velocity.x = 0;
	Velocity.y = 0;

	// Update player logic, sounds, etc.
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		Velocity.x = 10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		Velocity.x = -10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		Velocity.y = -10;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		Velocity.y = 10;

	// Effect the player velocity by gravity.
	//Velocity.y -= 0.2f;

	// Set the velocity and position.
	SetPosition(Velocity, true);
}
