#pragma once

class Vector3f
{
public:
	float& X() { return m_X; };

	float& Y() { return m_Y; };

	float& Z() { return m_Z; };

	Vector3f();
	Vector3f(float x, float y, float z);

	Vector3f operator+(const Vector3f& other);

	Vector3f operator-(const Vector3f& other);

	Vector3f operator*(const float& scalar);
private:
	float m_X, m_Y, m_Z;
};
