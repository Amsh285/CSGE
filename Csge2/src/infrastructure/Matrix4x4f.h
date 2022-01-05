#pragma once

#include <array>

#include <string>
#include <vector>

#include "MathHelper.h"

class Matrix4x4f
{
public:
	Matrix4x4f(const std::vector<std::vector<float>>& data);

	Matrix4x4f operator*(const Matrix4x4f& other) const;

	std::vector<float> GetOpenGlRepresentation() const;


	static Matrix4x4f Perspective(float fovy, float aspectRatio, float zNear, float zFar);

	static Matrix4x4f Translate(float x, float y, float z);
private:
	std::vector<std::vector<float>> m_Data;
};