#include <Vector2.hpp>
#include <Rect.hpp>
#include <Matrix.hpp>
#include <Shader.hpp>

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw() = 0;
	virtual void Update(unsigned int timestep) = 0;

	void SetPosition(float x, float y, bool relative = false);
	void SetPosition(Vector2 position, bool relative = false) { SetPosition(position.x, position.y, relative); }
	const Vector2 &GetPosition() { return Position; }
	const float GetX() { return Position.x; }
	const float GetY() { return Position.y; }

	void SetVelocity(float x, float y, bool relative = false);
	void SetVelocity(Vector2 velocity, bool relative = false) { SetVelocity(velocity.x, velocity.y, relative); }
	const Vector2 &GetVelocity() { return Velocity; }

	void SetAABB(float x1, float y1, float x2, float y2);
	void SetAABB(Vector2 p1, Vector2 p2) { SetAABB(p1.x, p1.y, p2.x, p2.y); }
	const Rect &GetAABB() { return AABB; }
	bool HasAABB();

	bool CheckCollision(Rect other);

protected:
	Rect AABB;
	Vector2 Position, Velocity;
	Matrix Matrix;
};