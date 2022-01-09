#pragma once

#include <cmath>

class Vector3f
{
public:
	static Vector3f Up() { return Vector3f(0.0f, 1.0f, 0.0f); };
	static Vector3f Forward() { return Vector3f(0.0f, 0.0f, -1.0f); };

	float& X() { return m_X; };

	float& Y() { return m_Y; };

	float& Z() { return m_Z; };

	Vector3f();
	Vector3f(float x, float y, float z);

	Vector3f operator+(const Vector3f& other) const;

	Vector3f operator-(const Vector3f& other) const;

	Vector3f operator*(const float& scalar) const;

	float operator*(const Vector3f& other) const;

	Vector3f CrossProduct(const Vector3f& value) const;

	float GetLength() const;

	float GetLengthSqrt() const;

	Vector3f Normalize() const;
private:
	float m_X, m_Y, m_Z;
};
