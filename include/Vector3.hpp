#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>

class Vector3
{
public:

	Vector3(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
		: x(X), y(Y), z(Z)
	{
	}

	// Increment / Decrement operators.

	Vector3& operator++() // Prefix inc operator
	{
		x++;
		y++;
		z++;
		return *this;
	}
	
	Vector3 operator++(int) // Postfix inc operator
	{
		Vector3 tmp(*this);
		++(*this);
		return tmp;
	}

	Vector3& operator--() // Prefix dec operator
	{
		x--;
		y--;
		z--;
		return *this;
	}

	Vector3 operator--(int) // Postfix dec operator
	{
		Vector3 tmp(*this);
		--(*this);
		return tmp;
	}

	//

	const Vector3& operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	const Vector3& operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	const Vector3 operator+(const Vector3& other) const
	{
		Vector3 tmp(*this);
		tmp.x += other.x;
		tmp.y += other.y;
		tmp.z += other.z;
		return tmp;
	}

	const Vector3 operator-(const Vector3& other) const
	{
		Vector3 tmp(*this);
		tmp.x -= other.x;
		tmp.y -= other.y;
		tmp.z -= other.z;
		return tmp;
	}

	// Negation
	const Vector3 operator-(void) const
	{
		return Vector3(-x, -y, -z);
	}

	// Uniform Scaling
	const Vector3& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}

	const Vector3 operator/(const float scalar) const
	{
		Vector3 tmp(*this);
		return tmp /= scalar;
	}

	const Vector3& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	const Vector3 operator*(const float scalar) const
	{
		Vector3 tmp(*this);
		return tmp *= scalar;
	}

	// Dot Product

	float operator*(const Vector3& other) const
	{
		return (x * other.x + y * other.y + z * other.z);
	}

	Vector3 CrossProduct(const Vector3& other) const
	{
		return Vector3((y * other.z) - (z * other.y), -((x * other.z) - (z * other.x)), (x * other.y) - (y * other.x));
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

	Vector3 Normalized() const
	{
		return *this / Length();
	}

	// Distance
	float DistanceSq(const Vector3& other) const
	{
		return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z);
	}

	float Distance(const Vector3& other) const
	{
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) + (z - other.z) * (z - other.z));
	}

	// Equality Operators

	bool operator==(const Vector3& other) const
	{
		return (other.x == x && other.y == y && other.z == z);
	}

	bool operator!=(const Vector3& other) const
	{
		return (other.x != x || other.y != y || other.z != z);
	}

	// Comparison Operators

	bool operator>(const Vector3& other) const
	{
		return (x > other.x && y > other.y && z > other.z);
	}

	bool operator>=(const Vector3& other) const
	{
		return !(*this < other);
	}

	bool operator<(const Vector3& other) const
	{
		return (x < other.x && y < other.y && z < other.z);
	}

	bool operator<=(const Vector3& other) const
	{
		return !(*this > other);
	}

	float x, y, z;
};

#endif