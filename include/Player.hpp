#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <Vector2.hpp>

class Player
{
public:
	Player()
	{
	}

	~Player()
	{
	}

	void SetPosition(const Vector2& inPosition, bool inRelative);
	void SetPosition(float X, float Y, bool inRelative);

	const Vector2& GetPosition() const
	{
		return position;
	}

	const float GetX() const
	{
		return position.x;
	}

	const float GetY() const
	{
		return position.y;
	}

	void SetVelocity(const Vector2& inVelocity, bool inRelative);
	void SetVelocity(float X, float Y, bool inRelative);

	const Vector2& GetVelocity() const
	{
		return velocity;
	}
private:
	sf::Texture tex;
	Vector2 position, velocity;
};

#endif