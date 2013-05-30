#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <Vector2.hpp>
#include <Rect.hpp>
#include <Matrix.hpp>

#include <Shader.hpp>
#include <AnimatedSprite.hpp>

class GameObject
{
public:
	GameObject(const std::string& inTexFilename, const std::string& inAnimFilename = "");
	~GameObject();

	virtual void Draw() = 0;
	virtual void Update(unsigned int timestep) = 0;

	void SetPosition(float x, float y, bool relative = false);
	void SetPosition(Vector2 inPosition, bool relative = false) { SetPosition(inPosition.x, inPosition.y, relative); }
	const Vector2 &GetPosition() { return position; }
	const float GetX() { return position.x; }
	const float GetY() { return position.y; }

	void SetVelocity(float x, float y, bool relative = false);
	void SetVelocity(Vector2 inVelocity, bool relative = false) { SetVelocity(inVelocity.x, inVelocity.y, relative); }
	const Vector2 &GetVelocity() { return velocity; }

	void SetAABB(float x1, float y1, float x2, float y2);
	void SetAABB(Vector2 p1, Vector2 p2) { SetAABB(p1.x, p1.y, p2.x, p2.y); }
	const Rect &GetAABB() { return AABB; }
	bool HasAABB();

	bool CheckCollision(Rect other);

	const Matrix& GetMatrix() const;

protected:
	Rect AABB;
	Vector2 position, velocity;

	// Rendering components.
	AnimatedSprite sprite;
};

#endif