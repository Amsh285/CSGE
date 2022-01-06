#include "Transforms.h"


Transforms::Transforms()
	: m_Scale(1.0f, 1.0f, 1.0f)
{
}

const Vector3f Transforms::GetFulcrum()
{
	return m_Position + m_Scale * 0.5f;
}


Matrix4x4f Transforms::GetTransformationMatrix()
{
	Vector3f fulcrum = GetFulcrum();

	Matrix4x4f translate = Matrix4x4f::Translate(m_Position);
	Matrix4x4f scale = Matrix4x4f::Scale(m_Scale);

	Matrix4x4f rotateX = Matrix4x4f::RotationX(m_Rotation.X());
	Matrix4x4f rotateY = Matrix4x4f::RotationY(m_Rotation.Y());
	Matrix4x4f rotateZ = Matrix4x4f::RotationZ(m_Rotation.Z());

	// Note: Order!
	return translate * scale * rotateZ * rotateX * rotateY;
}
