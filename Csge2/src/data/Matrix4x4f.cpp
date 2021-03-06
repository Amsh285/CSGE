#include "Matrix4x4f.h"

Matrix4x4f::Matrix4x4f(
	float v00, float v01, float v02, float v03,
	float v10, float v11, float v12, float v13,
	float v20, float v21, float v22, float v23,
	float v30, float v31, float v32, float v33)
{
	std::vector<std::vector<float>> data;

	std::vector<float> row0;
	std::vector<float> row1;
	std::vector<float> row2;
	std::vector<float> row3;

	row0.push_back(v00);
	row0.push_back(v01);
	row0.push_back(v02);
	row0.push_back(v03);

	row1.push_back(v10);
	row1.push_back(v11);
	row1.push_back(v12);
	row1.push_back(v13);

	row2.push_back(v20);
	row2.push_back(v21);
	row2.push_back(v22);
	row2.push_back(v23);

	row3.push_back(v30);
	row3.push_back(v31);
	row3.push_back(v32);
	row3.push_back(v33);

	m_Data.push_back(row0);
	m_Data.push_back(row1);
	m_Data.push_back(row2);
	m_Data.push_back(row3);
}

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

float Matrix4x4f::Determinant() const
{
	float factor00 = m_Data[0][0];

	Matrix3x3f m00(
		m_Data[1][1], m_Data[1][2], m_Data[1][3],
		m_Data[2][1], m_Data[2][2], m_Data[2][3],
		m_Data[3][1], m_Data[3][2], m_Data[3][3]
	);

	float factor01 = -1.0f * m_Data[0][1];

	Matrix3x3f m01 (
		m_Data[1][0], m_Data[1][2], m_Data[1][3],
		m_Data[2][0], m_Data[2][2], m_Data[2][3],
		m_Data[3][0], m_Data[3][2], m_Data[3][3]
	);

	float factor02 = m_Data[0][2];

	Matrix3x3f m02(
		m_Data[1][0], m_Data[1][1], m_Data[1][3],
		m_Data[2][0], m_Data[2][1], m_Data[2][3],
		m_Data[3][0], m_Data[3][1], m_Data[3][3]
	);

	float factor03 = -1.0f * m_Data[0][3];

	Matrix3x3f m03(
		m_Data[1][0], m_Data[1][1], m_Data[1][2],
		m_Data[2][0], m_Data[2][1], m_Data[2][2],
		m_Data[3][0], m_Data[3][1], m_Data[3][2]
	);

	float det1 = m00.Determinant();
	float det2 = m01.Determinant();
	float det3 = m02.Determinant();
	float det4 = m03.Determinant();

	float f1 = factor00 * m00.Determinant();
	float f2 = factor01 * m01.Determinant();
	float f3 = factor02 * m02.Determinant();
	float f4 = factor03 * m03.Determinant();

	return factor00 * m00.Determinant() + factor01 * m01.Determinant()
		+ factor02 * m02.Determinant() + factor03 * m03.Determinant();
}

Matrix4x4f Matrix4x4f::Transpose() const
{
	return Matrix4x4f(
		m_Data[0][0], m_Data[1][0], m_Data[2][0], m_Data[3][0],
		m_Data[0][1], m_Data[1][1], m_Data[2][1], m_Data[3][1],
		m_Data[0][2], m_Data[1][2], m_Data[2][2], m_Data[3][2],
		m_Data[0][3], m_Data[1][3], m_Data[2][3], m_Data[3][3]
	);
}

std::vector<float> Matrix4x4f::GetOpenGlRepresentation() const
{
	std::vector<float> matOpenGl;

	for (size_t col = 0; col < 4; col++)
		for (size_t row = 0; row < 4; row++)
			matOpenGl.push_back(m_Data[row][col]);

	return matOpenGl;
}

// see https://www.youtube.com/watch?v=U0_ONQQ5ZNM&ab_channel=BrendanGalea
Matrix4x4f Matrix4x4f::Perspective(float fovy, float aspectRatio, float zNear, float zFar)
{
	float fovyRadHalf = MathHelper::convertToRad(fovy / 2);

	float t = zNear * tan(fovyRadHalf);
	float b = -t;

	float r = t * aspectRatio;
	float l = -r;

	float n = zNear, f = zFar;

	return Matrix4x4f({
		{(2 * n) / (r - l)		, 0.0f					, (r + l) / (r - l)			, 0.0f},
		{0.0f					, (2 * n) / (t - b)		, (t + b) / (t - b)			, 0.0f},
		{0.0f					, 0.0f					, -((f + n) / (f - n))		, -((2 * f * n) / (f - n))},
		{0.0f					, 0.0f					, -1.0f						, 0.0f}
	});
}

Matrix4x4f Matrix4x4f::LookAt(const Vector3f& position, const Vector3f& direction, const Vector3f& up)
{
	Vector3f forward = (direction - position).Normalize();

	Vector3f right = forward
		.CrossProduct(up)
		.Normalize();

	Vector3f realUp = right
		.CrossProduct(forward)
		.Normalize();

	Matrix4x4f translation = Matrix4x4f::Translate(position * (-1));

	Vector3f backwards = forward * (-1);

	Matrix4x4f align = Matrix4x4f(
		right.X(), realUp.X(), backwards.X(), 0.0f,
		right.Y(), realUp.Y(), backwards.Y(), 0.0f,
		right.Z(), realUp.Z(), backwards.Z(), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	return align * translation;
}

Matrix4x4f Matrix4x4f::Scale(Vector3f scale)
{
	return Scale(scale.X(), scale.Y(), scale.Z());
}

Matrix4x4f Matrix4x4f::Scale(float x, float y, float z)
{
	return Matrix4x4f(
		x		, 0.0f		, 0.0f		, 0.0f,
		0.0f	, y			, 0.0f		, 0.0f,
		0.0f	, 0.0f		, z			, 0.0f,
		0.0f	, 0.0f		, 0.0f		, 1.0f
	);
}

Matrix4x4f Matrix4x4f::Translate(Vector3f translationsVector)
{
	return Translate(translationsVector.X(), translationsVector.Y(), translationsVector.Z());
}

Matrix4x4f Matrix4x4f::Translate(float x, float y, float z)
{
	return Matrix4x4f({
		{ 1.0f		, .0f		, 0.0f		, x },
		{ 0.0f		, 1.0f		, 0.0f		, y },
		{ 0.0f		, 0.0f		, 1.0f		, z },
		{ 0.0f		, 0.0f		, 0.0f		, 1.0f },
	});
}

Matrix4x4f Matrix4x4f::RotationX(float angle)
{
	float a = MathHelper::convertToRad(angle);

	return Matrix4x4f(
			1.0f	, 0.0f		, 0.0f		, 0.0f,
			0.0f	, cos(a)	, -sin(a)	, 0.0f,
			0.0f	, sin(a)	, cos(a)	, 0.0f,
			0.0f	, 0.0f		, 0.0f		, 1.0f
	);
}

Matrix4x4f Matrix4x4f::RotationY(float angle)
{
	float a = MathHelper::convertToRad(angle);

	return Matrix4x4f(
			cos(a)	, 0.0f		, sin(a)	, 0.0f,
			0.0f	, 1.0f		, 0.0f		, 0.0f,
			-sin(a)	, 0.0f		, cos(a)	, 0.0f,
			0.0f	, 0.0f		, 0.0f		, 1.0f
	);
}

Matrix4x4f Matrix4x4f::RotationZ(float angle)
{
	float a = MathHelper::convertToRad(angle);

	return Matrix4x4f(
			cos(a)	, -sin(a)	, 0.0f		, 0.0f,
			sin(a)	, cos(a)	, 0.0f		, 0.0f,
			0.0f	, 0.0f		, 1.0f		, 0.0f,
			0.0f	, 0.0f		, 0.0f		, 1.0f
	);
}
