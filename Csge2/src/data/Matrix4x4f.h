#pragma once

#include <array>
#include <cmath>
#include <string>
#include <vector>

#include "../infrastructure/MathHelper.h"
#include "Vector3f.h"

class Matrix4x4f
{
public:
	Matrix4x4f(
		float v00, float v01, float v02, float v03,
		float v10, float v11, float v12, float v13,
		float v20, float v21, float v22, float v23,
		float v30, float v31, float v32, float v33);

	Matrix4x4f(const std::vector<std::vector<float>>& data);

	Matrix4x4f operator*(const Matrix4x4f& other) const;

	std::vector<float> GetOpenGlRepresentation() const;

	static Matrix4x4f Perspective(float fovy, float aspectRatio, float zNear, float zFar);

	static Matrix4x4f Scale(Vector3f scale);

	static Matrix4x4f Scale(float x, float y, float z);

	static Matrix4x4f Translate(Vector3f translationsVector);

	static Matrix4x4f Translate(float x, float y, float z);

	static Matrix4x4f RotationX(float angle);

	static Matrix4x4f RotationY(float angle);

	static Matrix4x4f RotationZ(float angle);
private:
	std::vector<std::vector<float>> m_Data;
};