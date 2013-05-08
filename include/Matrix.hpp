#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

#include <Vector3.hpp>
#include <Quaternion.hpp>

class Matrix
{
public:
	Matrix()
	{
		matData.m[0] = 1; matData.m[1] = 0; matData.m[2] = 0; matData.m[3] = 0;
		matData.m[4] = 0; matData.m[5] = 1; matData.m[6] = 0; matData.m[7] = 0;
		matData.m[8] = 0; matData.m[9] = 0; matData.m[10] = 1; matData.m[11] = 0;
		matData.m[12] = 0; matData.m[13] = 0; matData.m[14] = 0; matData.m[15] = 1;
	}

	Matrix(float M0, float M1, float M2, float M3,
		   float M4, float M5, float M6, float M7,
		   float M8, float M9, float M10, float M11,
		   float M12, float M13, float M14, float M15)
	{
		matData.m[0] = M0; matData.m[1] = M1; matData.m[2] = M2; matData.m[3] = M3;
		matData.m[4] = M4; matData.m[5] = M5; matData.m[6] = M6; matData.m[7] = M7;
		matData.m[8] = M8; matData.m[9] = M9; matData.m[10] = M10; matData.m[11] = M11;
		matData.m[12] = M12; matData.m[13] = M13; matData.m[14] = M14; matData.m[15] = M15;
	}

	// Operators

	const Matrix& operator+=(const Matrix& other)
	{
		matData.mat[0][0] += other[0][0];
		matData.mat[0][1] += other[0][1];
		matData.mat[0][2] += other[0][2];
		matData.mat[0][3] += other[0][3];

		matData.mat[1][0] += other[1][0];
		matData.mat[1][1] += other[1][1];
		matData.mat[1][2] += other[1][2];
		matData.mat[1][3] += other[1][3];
		
		matData.mat[2][0] += other[2][0];
		matData.mat[2][1] += other[2][1];
		matData.mat[2][2] += other[2][2];
		matData.mat[2][3] += other[2][3];
		
		matData.mat[3][0] += other[3][0];
		matData.mat[3][1] += other[3][1];
		matData.mat[3][2] += other[3][2];
		matData.mat[3][3] += other[3][3];

		return *this;
	}

	const Matrix operator+(const Matrix& other) const
	{
		Matrix tmp(*this);

		tmp[0][0] += other[0][0];
		tmp[0][1] += other[0][1];
		tmp[0][2] += other[0][2];
		tmp[0][3] += other[0][3];

		tmp[1][0] += other[1][0];
		tmp[1][1] += other[1][1];
		tmp[1][2] += other[1][2];
		tmp[1][3] += other[1][3];

		tmp[2][0] += other[2][0];
		tmp[2][1] += other[2][1];
		tmp[2][2] += other[2][2];
		tmp[2][3] += other[2][3];

		tmp[3][0] += other[3][0];
		tmp[3][1] += other[3][1];
		tmp[3][2] += other[3][2];
		tmp[3][3] += other[3][3];

		return tmp;
	}

	const Matrix& operator-=(const Matrix& other)
	{
		matData.mat[0][0] -= other[0][0];
		matData.mat[0][1] -= other[0][1];
		matData.mat[0][2] -= other[0][2];
		matData.mat[0][3] -= other[0][3];

		matData.mat[1][0] -= other[1][0];
		matData.mat[1][1] -= other[1][1];
		matData.mat[1][2] -= other[1][2];
		matData.mat[1][3] -= other[1][3];

		matData.mat[2][0] -= other[2][0];
		matData.mat[2][1] -= other[2][1];
		matData.mat[2][2] -= other[2][2];
		matData.mat[2][3] -= other[2][3];

		matData.mat[3][0] -= other[3][0];
		matData.mat[3][1] -= other[3][1];
		matData.mat[3][2] -= other[3][2];
		matData.mat[3][3] -= other[3][3];

		return *this;
	}

	const Matrix operator-(const Matrix& other) const
	{
		Matrix tmp(*this);

		tmp[0][0] -= other[0][0];
		tmp[0][1] -= other[0][1];
		tmp[0][2] -= other[0][2];
		tmp[0][3] -= other[0][3];

		tmp[1][0] -= other[1][0];
		tmp[1][1] -= other[1][1];
		tmp[1][2] -= other[1][2];
		tmp[1][3] -= other[1][3];

		tmp[2][0] -= other[2][0];
		tmp[2][1] -= other[2][1];
		tmp[2][2] -= other[2][2];
		tmp[2][3] -= other[2][3];

		tmp[3][0] -= other[3][0];
		tmp[3][1] -= other[3][1];
		tmp[3][2] -= other[3][2];
		tmp[3][3] -= other[3][3];

		return tmp;
	}

	const Matrix& operator*=(const Matrix& other)
	{
		matData.mat[0][0] = (matData.mat[0][0] * other[0][0]) + (matData.mat[0][1] * other[1][0]) + (matData.mat[0][2] * other[2][0]) + (matData.mat[0][3] * other[3][0]);
		matData.mat[0][1] = (matData.mat[0][0] * other[0][1]) + (matData.mat[0][1] * other[1][1]) + (matData.mat[0][2] * other[2][1]) + (matData.mat[0][3] * other[3][1]);
		matData.mat[0][2] = (matData.mat[0][0] * other[0][2]) + (matData.mat[0][1] * other[1][2]) + (matData.mat[0][2] * other[2][2]) + (matData.mat[0][3] * other[3][2]);
		matData.mat[0][3] = (matData.mat[0][0] * other[0][3]) + (matData.mat[0][1] * other[1][3]) + (matData.mat[0][2] * other[2][3]) + (matData.mat[0][3] * other[3][3]);

		matData.mat[1][0] = (matData.mat[1][0] * other[0][0]) + (matData.mat[1][1] * other[1][0]) + (matData.mat[1][2] * other[2][0]) + (matData.mat[1][3] * other[3][0]);
		matData.mat[1][1] = (matData.mat[1][0] * other[0][1]) + (matData.mat[1][1] * other[1][1]) + (matData.mat[1][2] * other[2][1]) + (matData.mat[1][3] * other[3][1]);
		matData.mat[1][2] = (matData.mat[1][0] * other[0][2]) + (matData.mat[1][1] * other[1][2]) + (matData.mat[1][2] * other[2][2]) + (matData.mat[1][3] * other[3][2]);
		matData.mat[1][3] = (matData.mat[1][0] * other[0][3]) + (matData.mat[1][1] * other[1][3]) + (matData.mat[1][2] * other[2][3]) + (matData.mat[1][3] * other[3][3]);

		matData.mat[2][0] = (matData.mat[2][0] * other[0][0]) + (matData.mat[2][1] * other[1][0]) + (matData.mat[2][2] * other[2][0]) + (matData.mat[2][3] * other[3][0]);
		matData.mat[2][1] = (matData.mat[2][0] * other[0][1]) + (matData.mat[2][1] * other[1][1]) + (matData.mat[2][2] * other[2][1]) + (matData.mat[2][3] * other[3][1]);
		matData.mat[2][2] = (matData.mat[2][0] * other[0][2]) + (matData.mat[2][1] * other[1][2]) + (matData.mat[2][2] * other[2][2]) + (matData.mat[2][3] * other[3][2]);
		matData.mat[2][3] = (matData.mat[2][0] * other[0][3]) + (matData.mat[2][1] * other[1][3]) + (matData.mat[2][2] * other[2][3]) + (matData.mat[2][3] * other[3][3]);

		matData.mat[3][0] = (matData.mat[3][0] * other[0][0]) + (matData.mat[3][1] * other[1][0]) + (matData.mat[3][2] * other[2][0]) + (matData.mat[3][3] * other[3][0]);
		matData.mat[3][1] = (matData.mat[3][0] * other[0][1]) + (matData.mat[3][1] * other[1][1]) + (matData.mat[3][2] * other[2][1]) + (matData.mat[3][3] * other[3][1]);
		matData.mat[3][2] = (matData.mat[3][0] * other[0][2]) + (matData.mat[3][1] * other[1][2]) + (matData.mat[3][2] * other[2][2]) + (matData.mat[3][3] * other[3][2]);
		matData.mat[3][3] = (matData.mat[3][0] * other[0][3]) + (matData.mat[3][1] * other[1][3]) + (matData.mat[3][2] * other[2][3]) + (matData.mat[3][3] * other[3][3]);

		return *this;
	}

	const Matrix operator*(const Matrix& other) const
	{
		Matrix out = CreateIdentity();

		out[0][0] = (matData.mat[0][0] * other[0][0]) + (matData.mat[0][1] * other[1][0]) + (matData.mat[0][2] * other[2][0]) + (matData.mat[0][3] * other[3][0]);
		out[0][1] = (matData.mat[0][0] * other[0][1]) + (matData.mat[0][1] * other[1][1]) + (matData.mat[0][2] * other[2][1]) + (matData.mat[0][3] * other[3][1]);
		out[0][2] = (matData.mat[0][0] * other[0][2]) + (matData.mat[0][1] * other[1][2]) + (matData.mat[0][2] * other[2][2]) + (matData.mat[0][3] * other[3][2]);
		out[0][3] = (matData.mat[0][0] * other[0][3]) + (matData.mat[0][1] * other[1][3]) + (matData.mat[0][2] * other[2][3]) + (matData.mat[0][3] * other[3][3]);

		out[1][0] = (matData.mat[1][0] * other[0][0]) + (matData.mat[1][1] * other[1][0]) + (matData.mat[1][2] * other[2][0]) + (matData.mat[1][3] * other[3][0]);
		out[1][1] = (matData.mat[1][0] * other[0][1]) + (matData.mat[1][1] * other[1][1]) + (matData.mat[1][2] * other[2][1]) + (matData.mat[1][3] * other[3][1]);
		out[1][2] = (matData.mat[1][0] * other[0][2]) + (matData.mat[1][1] * other[1][2]) + (matData.mat[1][2] * other[2][2]) + (matData.mat[1][3] * other[3][2]);
		out[1][3] = (matData.mat[1][0] * other[0][3]) + (matData.mat[1][1] * other[1][3]) + (matData.mat[1][2] * other[2][3]) + (matData.mat[1][3] * other[3][3]);

		out[2][0] = (matData.mat[2][0] * other[0][0]) + (matData.mat[2][1] * other[1][0]) + (matData.mat[2][2] * other[2][0]) + (matData.mat[2][3] * other[3][0]);
		out[2][1] = (matData.mat[2][0] * other[0][1]) + (matData.mat[2][1] * other[1][1]) + (matData.mat[2][2] * other[2][1]) + (matData.mat[2][3] * other[3][1]);
		out[2][2] = (matData.mat[2][0] * other[0][2]) + (matData.mat[2][1] * other[1][2]) + (matData.mat[2][2] * other[2][2]) + (matData.mat[2][3] * other[3][2]);
		out[2][3] = (matData.mat[2][0] * other[0][3]) + (matData.mat[2][1] * other[1][3]) + (matData.mat[2][2] * other[2][3]) + (matData.mat[2][3] * other[3][3]);

		out[3][0] = (matData.mat[3][0] * other[0][0]) + (matData.mat[3][1] * other[1][0]) + (matData.mat[3][2] * other[2][0]) + (matData.mat[3][3] * other[3][0]);
		out[3][1] = (matData.mat[3][0] * other[0][1]) + (matData.mat[3][1] * other[1][1]) + (matData.mat[3][2] * other[2][1]) + (matData.mat[3][3] * other[3][1]);
		out[3][2] = (matData.mat[3][0] * other[0][2]) + (matData.mat[3][1] * other[1][2]) + (matData.mat[3][2] * other[2][2]) + (matData.mat[3][3] * other[3][2]);
		out[3][3] = (matData.mat[3][0] * other[0][3]) + (matData.mat[3][1] * other[1][3]) + (matData.mat[3][2] * other[2][3]) + (matData.mat[3][3] * other[3][3]);

		return out;
	}

	// Equality Operators

	bool operator==(const Matrix& other) const
	{
		for(int i = 0; i < 16; i++)
		{
			if(matData.m[i] != other.matData.m[i])
				return false;
		}
		return true;
	}

	bool operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}

	// Array Operator
	float* operator[](int j)
	{
		return matData.m + j * 4;
	}

	const float* operator[](int j) const
	{
		return matData.m + j * 4;
	}

	// Functions
	static Matrix CreateIdentity()
	{
		return Matrix(1.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 1.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f);
	}

	static Matrix CreateTranslation(const Vector3& vec)
	{
		Matrix m = CreateIdentity();
		m[3][0] = vec.x;
		m[3][1] = vec.y;
		m[3][2] = vec.z;
		return m;
	}

	static Matrix CreateTranslation(float X, float Y, float Z)
	{
		Matrix m = CreateIdentity();
		m[3][0] = X;
		m[3][1] = Y;
		m[3][2] = Z;
		return m;
	}

	static Matrix CreateScale(const Vector3& scale)
	{
		Matrix m = CreateIdentity();
		m[0][0] = scale.x;
		m[1][1] = scale.y;
		m[2][2] = scale.z;
		return m;
	}

	static Matrix CreateScale(float X, float Y, float Z)
	{
		Matrix m = CreateIdentity();
		m[0][0] = X;
		m[1][1] = Y;
		m[2][2] = Z;
		return m;
	}

	static Matrix CreateXRotation(float radians)
	{
		float cosine = cos(radians);
		float sine = sin(radians);

		Matrix m = CreateIdentity();
		m[1][1] = cosine;
		m[1][2] = -sine;
		m[2][1] = sine;
		m[2][2] = cosine;
		return m;
	}

	static Matrix CreateYRotation(float radians)
	{
		float cosine = cos(radians);
		float sine = sin(radians);

		Matrix m = CreateIdentity();
		m[0][0] = cosine;
		m[0][2] = sine;
		m[2][0] = -sine;
		m[2][2] = cosine;
		return m;
	}

	static Matrix CreateZRotation(float radians)
	{
		float cosine = cos(radians);
		float sine = sin(radians);

		Matrix m = CreateIdentity();
		m[0][0] = cosine;
		m[0][1] = -sine;
		m[1][0] = sine; 
		m[1][1] = cosine;
		return m;
	}

	static Matrix OrthoProjection(float left, float right, float bottom, float top, float nearVal, float farVal)
	{
		Matrix m = CreateIdentity();

		float tx = -(right + left) / (right - left);
		float ty = -(top + bottom) / (top - bottom);
		float tz = -(farVal + nearVal) / (farVal - nearVal);

		m[0][0] = 2 / (right - left);
		m[1][1] = 2 / (top - bottom);
		m[2][2] = -2 / (farVal - nearVal);
		
		m[3][0] = tx;
		m[3][1] = ty;
		m[3][2] = tz;

		return m;
	}

	static Matrix Perspective(float fovy, float aspect, float nearVal, float farVal)
	{
		Matrix m = CreateIdentity();
		float ran = tan(fovy * 3.14159265f / 360.0f) * nearVal;
		float left = -ran * aspect;
		float right = ran * aspect;
		float top = ran;
		float bottom = -ran;

		m[0][0] = (2.0f * nearVal) / (right - left);
		m[1][1] = (2.0f * nearVal) / (top - bottom);
		m[2][2] = -(farVal + nearVal) / (farVal - nearVal);
		m[2][3] = -1.0f;
		m[3][2] = -(2.0f * farVal * nearVal) / (farVal - nearVal);

		return m;
	}

	static Matrix CreateLookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		Matrix m = CreateIdentity();

		Vector3 zax = (eye - target).Normalized();
		Vector3 xax = up.CrossProduct(zax).Normalized();
		Vector3 yax = zax.CrossProduct(xax);

		m[0][0] = xax.x;
		m[0][1] = yax.x;
		m[0][2] = zax.x;

		m[1][0] = xax.y;
		m[1][1] = yax.y;
		m[1][2] = zax.y;

		m[2][0] = xax.z;
		m[2][1] = yax.z;
		m[2][2] = zax.z;
		
		m[3][0] = -(xax * eye);
		m[3][1] = -(yax * eye);
		m[3][2] = -(zax * eye);

		return m;
	}

	static Vector3 GetVectorTransform(const Matrix& mat, const Vector3& vec)
	{
		return Vector3((vec.x * mat[0][0]) + (vec.y * mat[1][0]) + (vec.z * mat[2][0]),
					   (vec.x * mat[0][1]) + (vec.y * mat[1][1]) + (vec.z * mat[2][1]),
					   (vec.x * mat[0][2]) + (vec.y * mat[1][2]) + (vec.z * mat[2][2]));
	}

	static Matrix CreateFromQuaternion(const Quaternion& quat)
	{
		Quaternion nq = quat.Normalized();
		Matrix m(1.0f - 2.0f * nq.y * nq.y - 2.0f * nq.z * nq.z, 2.0f * nq.x * nq.y - 2.0f * nq.z * nq.w, 2.0f * nq.x * nq.z + 2.0f * nq.y * nq.w, 0.0f,
				2.0f * nq.x * nq.y + 2.0f * nq.z * nq.w, 1.0f - 2.0f * nq.x * nq.x - 2.0f * nq.z * nq.z, 2.0f * nq.y * nq.z - 2.0f * nq.x * nq.w, 0.0f,
				2.0f * nq.x * nq.z - 2.0f * nq.y * nq.w, 2.0f * nq.y * nq.z + 2.0f * nq.x * nq.w, 1.0f - 2.0f * nq.x * nq.x - 2.0f * nq.y * nq.y, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		return m ;
	}

	////
	std::vector<float> GetMatrix() const
	{
		std::vector<float> v;
		for(int i = 0; i < 16; i++)
			v.push_back(matData.m[i]);
		return v;
	}

private:
	union
	{
		float m[16];
		float mat[4][4];
	} matData;
};

#endif