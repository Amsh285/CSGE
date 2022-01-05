#pragma once

class Vector3f
{
public:
	const float& X() { return m_X; };
	void SetX(float x) { m_X = x; };

	const float& Y() { return m_Y; };
	void SetY(float y) { m_Y = y; };

	const float& Z() { return m_Z; };
	void SetZ(float z) { m_Z = z; };

	Vector3f();
	Vector3f(float x, float y, float z);

	Vector3f operator+(const Vector3f& other);

	Vector3f operator-(const Vector3f& other);
private:
	float m_X, m_Y, m_Z;
};
