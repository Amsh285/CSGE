#pragma once

#include "../infrastructure/Matrix4x4f.h"
#include "Vector3f.h"

class Transform
{
public:
	Vector3f& GetPosition() { return m_Position; };

	Vector3f& GetRotation() { return m_Rotation; };

	Vector3f& GetScale() { return m_Scale; };

	Transform();

	Matrix4x4f GetInplaceRotation();
private:
	Vector3f m_Position;
	Vector3f m_Rotation;
	Vector3f m_Scale;
};
