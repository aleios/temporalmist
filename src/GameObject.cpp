#include <GameObject.hpp>

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(float x, float y, bool relative)
{
	if (relative)
	{
		Position.x += x;
		Position.y += y;
	}
	else
	{
		Position.x = x;
		Position.y = y;
	}
}

void GameObject::SetVelocity(float x, float y, bool relative)
{
	if (relative)
	{
		Velocity.x += x;
		Velocity.y += y;
	}
	else
	{
		Velocity.x = x;
		Velocity.y = y;
	}
}

void GameObject::SetAABB(float x1, float y1, float x2, float y2)
{
	AABB.Set(x1, y1, x2, y2);
}

bool GameObject::HasAABB()
{
	Vector2 p1 = AABB.GetStart();
	Vector2 p2 = AABB.GetStart();

	if (p1.x == 0 && p1.y == 0 && p1.x == p2.x && p1.y == p2.y)
		return false;

	return true;
}

bool GameObject::CheckCollision(Rect other)
{
	if (!HasAABB())
		return false;

	// if AABB is inside other collision is missed, so reverse check
	if (AABB.Intersect(other) || other.Intersect(AABB))
		return true;

	return false;
}
