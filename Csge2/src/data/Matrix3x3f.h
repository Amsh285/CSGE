#pragma once

#include <vector>

#include "../infrastructure/MathHelper.h"
#include "Vector3f.h"

class Matrix3x3f
{
public:
	Matrix3x3f() : Matrix3x3f(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	) {};

	Matrix3x3f(
		float v00, float v01, float v02,
		float v10, float v11, float v12,
		float v20, float v21, float v22);
	
	Matrix3x3f Transpose() const;

	Vector3f operator*(Vector3f value) const;

	float Determinant() const;

	static Matrix3x3f RotationX(const float& angle);
	static Matrix3x3f RotationY(const float& angle);
private:
	std::vector<std::vector<float>> m_Data;
};

