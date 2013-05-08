#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <Vector2.hpp>
#include <Matrix.hpp>

class Camera
{
public:
	Camera(const Vector2& inPosition = Vector2(), float inRotation = 0.0f)
		: position(inPosition), rotation(inRotation)
	{
	}

	~Camera()
	{
	}

	void Update()
	{
		viewMatrix = Matrix::CreateTranslation(position.x, position.y, 0) * Matrix::CreateZRotation(rotation);
	}

	void SetPosition(const Vector2& inPosition)
	{
		position = inPosition;
	}

	void SetRotation(float inRotation)
	{
		rotation = inRotation;
	}

	const Matrix GetCameraMatrix() const
	{
		return viewMatrix;
	}
private:
	Matrix viewMatrix;
	Vector2 position;
	float rotation;
};

#endif