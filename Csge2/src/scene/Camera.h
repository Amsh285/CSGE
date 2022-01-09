#pragma once

#include "../data/Matrix3x3f.h"
#include "../data/Vector3f.h"
#include "../geometry/Transforms.h"
#include "../infrastructure/MathHelper.h"


class Camera
{
public:
	const float GetRotationAngleX() { return m_Transform.Rotation().X(); };

	const float GetRotationAngleY() { return m_Transform.Rotation().Y(); };

	const Vector3f GetPosition() { return m_Transform.Position(); };
	void SetPosition(const Vector3f& position) { m_Transform.Position() = position; };

	const Vector3f& GetDirection() const { return m_direction; };

	Camera();

	void SetAngles(const float& angleX, const float& angleY);

	void AlignDirection();
	void Reset();
private:
	/*void RotateX();
	void RotateY();*/

	// Scale won´t be used. as rotationZ due to time constraints.
	// Later on i could use scale probably to alter the frustum.
	// Maybe implement a Frustum class that can be scaled with Transform.Scale.
	// For rotations i will use Euler Angles, this isn´t optimal but i don´t have time for Quarternions.
	Transforms m_Transform;
	Vector3f m_direction;
};

