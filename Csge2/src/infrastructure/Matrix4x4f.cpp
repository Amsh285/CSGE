#include "Matrix4x4f.h"

Matrix4x4f::Matrix4x4f(const std::vector<std::vector<float>>& data)
	: m_Data(data)
{
}

Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f& other) const
{
	std::vector<std::vector<float>> mat;

	for (size_t row = 0; row < 4; row++)
	{
		std::vector<float> dotProducts;

		for (size_t otherCol = 0; otherCol < 4; otherCol++)
		{
			float dotProduct = 0;

			for (size_t col = 0; col < 4; col++)
				dotProduct += m_Data[row][col] * other.m_Data[col][otherCol];
			
			dotProducts.push_back(dotProduct);
		}

		mat.push_back(dotProducts);
	}

	return Matrix4x4f(mat);
}

std::vector<float> Matrix4x4f::GetOpenGlRepresentation() const
{
	std::vector<float> matOpenGl;

	for (size_t col = 0; col < 4; col++)
		for (size_t row = 0; row < 4; row++)
			matOpenGl.push_back(m_Data[row][col]);

	return matOpenGl;
}

Matrix4x4f Matrix4x4f::Perspective(float fovy, float aspectRatio, float zNear, float zFar)
{
	float fovyRadHalf = MathHelper::convertToRad(fovy / 2);

	float t = zNear * tan(fovyRadHalf);
	float b = -t;

	float r = t * aspectRatio;
	float l = -r;

	float n = zNear, f = zFar;

	return Matrix4x4f({
		{(2 * n) / (r - l)		, .0f					, (r + l) / (r - l)			, .0f},
		{.0f					, (2 * n) / (t - b)		, (t + b) / (t - b)			, .0f},
		{.0f					, .0f					, -((f + n) / (f - n))		, -((2 * f * n) / (f - n))},
		{.0f					, .0f					, -1.0f						, .0f}
	});
}

Matrix4x4f Matrix4x4f::Translate(float x, float y, float z)
{
	return Matrix4x4f({
		{ 1.0f		, .0f		, .0f		, x },
		{ .0f		, 1.0f		, .0f		, y },
		{ .0f		, .0f		, 1.0f		, z },
		{ .0f		, .0f		, .0f		, 1.0f },
	});
}
