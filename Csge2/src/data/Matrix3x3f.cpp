#include "Matrix3x3f.h"

Matrix3x3f::Matrix3x3f(float v00, float v01, float v02, float v10, float v11, float v12, float v20, float v21, float v22)
{
	std::vector<float> row0;
	std::vector<float> row1;
	std::vector<float> row2;

	row0.push_back(v00);
	row0.push_back(v01);
	row0.push_back(v02);

	row1.push_back(v10);
	row1.push_back(v11);
	row1.push_back(v12);

	row2.push_back(v20);
	row2.push_back(v21);
	row2.push_back(v22);

	m_Data.push_back(row0);
	m_Data.push_back(row1);
	m_Data.push_back(row2);
}

Matrix3x3f Matrix3x3f::Transpose() const
{
	return Matrix3x3f(
		m_Data[0][0], m_Data[1][0], m_Data[2][0],
		m_Data[0][1], m_Data[1][1], m_Data[2][1],
		m_Data[0][1], m_Data[1][2], m_Data[2][2]
	);
}

Vector3f Matrix3x3f::operator*(Vector3f value) const
{
	float x = value.X(), y = value.Y(), z = value.Z();

	return Vector3f(
		x * m_Data[0][0] + y * m_Data[0][1] + z * m_Data[0][2],
		x * m_Data[1][0] + y * m_Data[1][1] + z * m_Data[1][2],
		x * m_Data[2][0] + y * m_Data[2][1] + z * m_Data[2][2]
	);
}

float Matrix3x3f::Determinant() const
{
	return m_Data[0][0] * m_Data[1][1] * m_Data[2][2]
		+ m_Data[0][1] * m_Data[1][2] * m_Data[2][0]
		+ m_Data[0][2] * m_Data[1][0] * m_Data[2][1]

		- m_Data[2][0] * m_Data[1][1] * m_Data[0][2]
		- m_Data[2][1] * m_Data[1][2] * m_Data[0][0]
		- m_Data[2][2] * m_Data[1][0] * m_Data[0][1];
}

Matrix3x3f Matrix3x3f::RotationX(const float& angle)
{
	float a = MathHelper::convertToRad(angle);

	return Matrix3x3f(
		1.0f		, 0.0f		, 0.0f,
		0.0f		, cos(a)	, -sin(a),
		0.0f		, sin(a)	, cos(a)
	);
}

Matrix3x3f Matrix3x3f::RotationY(const float& angle)
{
	float a = MathHelper::convertToRad(angle);

	return Matrix3x3f(
		cos(a)		, 0.0f		, sin(a),
		0.0f		, 1.0f		, 0.0f,
		-sin(a)		, 0.0f		, cos(a)
	);
}
