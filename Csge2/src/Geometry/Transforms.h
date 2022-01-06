#pragma once

#include "../data/Matrix4x4f.h"
#include "../data/Vector3f.h"

class Transforms
{
public:
	Vector3f& Position() { return m_Position; };

	Vector3f& Rotation() { return m_Rotation; };

	Vector3f& Scale() { return m_Scale; };

	Transforms();

	const Vector3f GetFulcrum();

	Matrix4x4f GetTransformationMatrix();
private:
	Vector3f m_Position;
	Vector3f m_Rotation;
	Vector3f m_Scale;
};
