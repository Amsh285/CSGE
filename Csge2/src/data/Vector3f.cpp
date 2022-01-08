#include "Vector3f.h"

Vector3f::Vector3f()
	: Vector3f(0.0f, 0.0f, 0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
	: m_X(x), m_Y(y), m_Z(z)
{
}

Vector3f Vector3f::operator+(const Vector3f& other) const
{
	return Vector3f(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
}

Vector3f Vector3f::operator-(const Vector3f& other) const
{
	return Vector3f(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
}

Vector3f Vector3f::operator*(const float& scalar) const
{
	return Vector3f(m_X * scalar, m_Y * scalar, m_Z * scalar);
}

Vector3f Vector3f::CrossProduct(const Vector3f& value) const
{
	return Vector3f(
		m_Y * value.m_Z - m_Z * value.m_Y,
		m_Z * value.m_X - m_X * value.m_Z,
		m_X * value.m_Y - m_Y * value.m_X
	);
}

float Vector3f::GetLength() const
{
	return pow(m_X, 2.0f) + pow(m_Y, 2.0f) + pow(m_Z, 2.0f);
}

float Vector3f::GetLengthSqrt() const
{
	return sqrt(GetLength());
}

Vector3f Vector3f::Normalize() const
{
	return (*this) * (1.0f / GetLengthSqrt());
}
