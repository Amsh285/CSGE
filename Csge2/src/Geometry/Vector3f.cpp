#include "Vector3f.h"

Vector3f::Vector3f()
	: Vector3f(0.0f, 0.0f, 0.0f)
{
}

Vector3f::Vector3f(float x, float y, float z)
	: m_X(x), m_Y(y), m_Z(z)
{
}

Vector3f Vector3f::operator+(const Vector3f& other)
{
	return Vector3f(m_X + other.m_X, m_Y + other.m_Y, m_Z + other.m_Z);
}

Vector3f Vector3f::operator-(const Vector3f& other)
{
	return Vector3f(m_X - other.m_X, m_Y - other.m_Y, m_Z - other.m_Z);
}
