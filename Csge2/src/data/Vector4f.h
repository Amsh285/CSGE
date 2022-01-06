#pragma once
class Vector4f
{
public:
	float& X() { return m_X; };
	float& Y() { return m_Y; };
	float& Z() { return m_Z; };
	float& H() { return m_H; };

	Vector4f();
	Vector4f(float x, float y, float z, float h);

	Vector4f Vector();
private:
	float m_X;
	float m_Y;
	float m_Z;
	float m_H;
};

