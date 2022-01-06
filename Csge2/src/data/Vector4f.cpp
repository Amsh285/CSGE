#include "Vector4f.h"

Vector4f::Vector4f()
	: Vector4f(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Vector4f::Vector4f(float x, float y, float z, float h)
	: m_X(x), m_Y(y), m_Z(z), m_H(h)
{
}

Vector4f Vector4f::Vector()
{
	return Vector4f(m_X, m_Y, m_Z, 0.0f);
}
