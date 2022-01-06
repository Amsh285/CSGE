#pragma once

#include<vector>

#include "Vector3f.h"
#include "Vector4f.h"

struct TextureCoord
{
	float x;
	float y;

	TextureCoord()
		: TextureCoord(0.0f, 0.0f)
	{
	}

	TextureCoord(float x, float y)
		: x(x), y(y)
	{
	}
};

class Vertex
{
public:
	Vector3f& Position() { return m_Position; };
	Vector4f& Color() { return m_Color; };
	TextureCoord& TextureCoordinate() { return m_TextureCoordinate; };
	unsigned int GetIndex() const { return m_Index; };

	Vertex(unsigned int index);
	Vertex(
		float posX, float posY, float posZ,
		float r, float g, float b, float a,
		float tX, float tY,
		unsigned int index);

	std::vector<float> GetVertexBuffer();
private:
	Vector3f m_Position;
	Vector4f m_Color;
	TextureCoord m_TextureCoordinate;

	unsigned int m_Index;
};

