#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <Vector3.hpp>

class Quaternion
{
public:
	Quaternion(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 1.0f)
		: x(X), y(Y), z(Z), w(W)
	{
	}

	Quaternion(const Vector3& vec, float scalar)
		: w(scalar)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
	}

	const Quaternion& operator*=(const Quaternion& other)
	{
		w = (w * other.w - x * other.x - y * other.y - z * other.z);
		x = (w * other.x + x * other.w + y * other.z - z * other.y);
		y = (w * other.y - x * other.z + y * other.w + z * other.x);
		z = (w * other.z + x * other.y - y * other.x + z * other.w);

		return *this;
	}

	// Multiply and Transform
	Quaternion operator*(const Quaternion& other) const
	{
		Quaternion tmp(*this);
		return tmp *= other;
	}

	// Divide
	Quaternion operator/(float scalar) const
	{
		return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
	}

	// Dot
	float Dot(const Quaternion& quat)
	{
		return x * quat.x + y * quat.y + z * quat.z + w * quat.w;
	}

	static float Dot(const Quaternion& q1, const Quaternion& q2)
	{
		return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
	}

	// Inverse
	const Quaternion& Inverse()
	{
		x = w;
		y = -x;
		z = -y;
		w = -z;
		*this / Dot(*this);

		return *this;
	}

	static Quaternion Inverse(const Quaternion& quat)
	{
		return Quaternion(quat.w, -quat.x, -quat.y, -quat.z) / Dot(quat, quat);
	}

	// Length
	float Length() const
	{
		return sqrt(w * w + x * x + y * y + z * z);
	}

	float LengthSquared() const
	{
		return w * w + x * x + y * y + z * z;
	}

	// Normalization
	Quaternion Normalized() const
	{
		Quaternion res(*this);
		float mag = Length();

		res.w /= mag;
		res.x /= mag;
		res.y /= mag;
		res.z /= mag;

		return res;
	}

	void Normalize()
	{
		float mag = Length();
		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}

	// Identity
	static Quaternion Identity()
	{
		return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Yaw, Pitch, roll
	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		Quaternion quat;
		quat.x = ((cos(yaw * 0.5f) * sin(pitch * 0.5f)) * cos(roll * 0.5f)) + ((sin(yaw * 0.5f) * cos(pitch * 0.5f)) * sin(roll * 0.5f));
		quat.y = ((sin(yaw * 0.5f) * cos(pitch * 0.5f)) * cos(roll * 0.5f)) - ((cos(yaw * 0.5f) * sin(pitch * 0.5f)) * sin(roll * 0.5f));
		quat.z = ((cos(yaw * 0.5f) * cos(pitch * 0.5f)) * sin(roll * 0.5f)) - ((sin(yaw * 0.5f) * sin(pitch * 0.5f)) * cos(roll * 0.5f));
		quat.w = ((cos(yaw * 0.5f) * cos(pitch * 0.5f)) * cos(roll * 0.5f)) + ((sin(yaw * 0.5f) * sin(pitch * 0.5f)) * sin(roll * 0.5f));
		return quat;
	}

	// Vector3 Transform
	static Vector3 GetVectorTransform(const Quaternion& quat, const Vector3& vec)
	{
		Vector3 qvec(quat.x, quat.y, quat.z);
		Vector3 v1 = qvec.CrossProduct(vec);
		Vector3 v2 = qvec.CrossProduct(v1);

		v1 *= (2 * quat.w);
		v2 *= 2;

		return vec + v1 + v2;//Vector3(quat.x * vec.x, quat.y * vec.y, quat.z * vec.z);
	}

	float x, y, z, w;
};

#endif