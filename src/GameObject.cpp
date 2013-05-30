#include <GameObject.hpp>

GameObject::GameObject(const std::string& inTexFilename, const std::string& inAnimFilename)
	: sprite(inTexFilename, inAnimFilename)
{
}

GameObject::~GameObject()
{
}

void GameObject::SetPosition(float x, float y, bool relative)
{
	if (relative)
	{
		position.x += x;
		position.y += y;
	}
	else
	{
		position.x = x;
		position.y = y;
	}
}

void GameObject::SetVelocity(float x, float y, bool relative)
{
	if (relative)
	{
		velocity.x += x;
		velocity.y += y;
	}
	else
	{
		velocity.x = x;
		velocity.y = y;
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

const Matrix& GameObject::GetMatrix() const
{
	return Matrix::CreateIdentity() * Matrix::CreateTranslation(position.x, position.y, 0);
}