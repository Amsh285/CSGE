#include "Camera.h"

Camera::Camera()
{
	m_Transform.Position() = Vector3f(0.0f, 0.0f, 0.0f);
	m_Transform.Rotation() = Vector3f(0.0f, 0.0f, 0.0f);
	m_Transform.Scale() = Vector3f(1.0f, 1.0f, 1.0f);

	m_direction = Vector3f(0.0f, 0.0f, -1.0f);
}

void Camera::SetAngles(const float& angleX, const float& angleY)
{
	m_Transform.Rotation().X() = angleX;
	m_Transform.Rotation().Y() = angleY;
	AlignDirection();
}

void Camera::AlignDirection()
{
	/*RotateY();
	RotateX();*/

	float pitch = MathHelper::convertToRad(m_Transform.Rotation().X());
	float yaw = MathHelper::convertToRad(m_Transform.Rotation().Y());

	// simplified rotation Matrices over Y and X
	// assumes initial direction (0.0f, 0.0f, -1.0f)
	m_direction = Vector3f(
		std::sin(yaw) * std::cos(pitch),
		(std::sin(pitch)),
		-(std::cos(yaw) * std::cos(pitch))
	);
}

void Camera::Reset()
{
	m_Transform.Position() = Vector3f(0.0f, 0.0f, 0.0f);
	m_Transform.Rotation() = Vector3f(0.0f, 0.0f, 0.0f);
	m_Transform.Scale() = Vector3f(1.0f, 1.0f, 1.0f);

	m_direction = Vector3f(0.0f, 0.0f, -1.0f);
	AlignDirection();
}
