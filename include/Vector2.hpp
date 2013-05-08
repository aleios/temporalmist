#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>

class Vector2
{
public:
	Vector2(float X = 0.0f, float Y = 0.0f)
		: x(X), y(Y)
	{
	}

	// Increment / Decrement operators.

	Vector2& operator++() // Prefix inc operator
	{
		x++;
		y++;
		return *this;
	}
	
	Vector2 operator++(int) // Postfix inc operator
	{
		Vector2 tmp(*this);
		++(*this);
		return tmp;
	}

	Vector2& operator--() // Prefix dec operator
	{
		x--;
		y--;
		return *this;
	}

	Vector2 operator--(int) // Postfix dec operator
	{
		Vector2 tmp(*this);
		--(*this);
		return tmp;
	}

	//

	const Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	const Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	const Vector2 operator+(const Vector2& other) const
	{
		Vector2 tmp(*this);
		tmp.x += other.x;
		tmp.y += other.y;
		return tmp;
	}

	const Vector2 operator-(const Vector2& other) const
	{
		Vector2 tmp(*this);
		tmp.x -= other.x;
		tmp.y -= other.y;
		return tmp;
	}

	// Negation
	const Vector2 operator-(void) const
	{
		return Vector2(-x, -y);
	}

	// Uniform Scaling
	const Vector2& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	const Vector2 operator/(const float scalar) const
	{
		Vector2 tmp(*this);
		return tmp /= scalar;
	}

	const Vector2& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	const Vector2 operator*(const float scalar) const
	{
		Vector2 tmp(*this);
		return tmp *= scalar;
	}

	// Dot Product.
	float operator*(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}

	// Length (magnitude)
	float LengthSq() const
	{
		return (*this * *this);
	}

	float Length() const
	{
		return sqrt((*this * *this));
	}

	// Normalization
	void Normalize()
	{
		*this /= Length();
	}

	Vector2 Normalized() const
	{
		return *this / Length();
	}

	// Scalar Projection
	float ScalarProjection(const Vector2& other) const
	{
		return (*this * other) / (other.Length());
	}

	// Vector Projection
	Vector2 VectorProjection(const Vector2& other) const
	{
		Vector2 proj = (other / other.Length()) * ScalarProjection(other);
		return proj;
	}

	// Equality Operators

	bool operator==(const Vector2& other) const
	{
		return (other.x == x && other.y == y);
	}

	bool operator!=(const Vector2& other) const
	{
		return (other.x != x || other.y != y);
	}

	// Comparison Operators

	bool operator>(const Vector2& other) const
	{
		return (x > other.x && y > other.y);
	}

	bool operator>=(const Vector2& other) const
	{
		return !(*this < other);
	}

	bool operator<(const Vector2& other) const
	{
		return (x < other.x && y < other.y);
	}

	bool operator<=(const Vector2& other) const
	{
		return !(*this > other);
	}

	float x, y;
};

#endif