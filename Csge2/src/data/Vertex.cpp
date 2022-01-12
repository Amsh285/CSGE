#include "Vertex.h"

Vertex::Vertex(unsigned int index)
	: Vertex(
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		index
	)
{
}

Vertex::Vertex(
	float posX, float posY, float posZ,
	float r, float g, float b, float a,
	float tX, float tY,
	unsigned int index)
	: m_Index(index)
{
	m_Position.X() = posX;
	m_Position.Y() = posY;
	m_Position.Z() = posZ;

	m_Color.X() = r;
	m_Color.Y() = g;
	m_Color.Z() = b;
	m_Color.H() = a;

	m_TextureCoordinate.x = tX;
	m_TextureCoordinate.y = tY;
}

std::vector<float> Vertex::GetVertexBuffer() const
{
	Vector3f pos = m_Position;
	Vector4f color = m_Color;

	return std::vector<float>{
		pos.X(), pos.Y(), pos.Z(),
		color.X(), color.Y(), color.Z(), color.H(),
		m_TextureCoordinate.x, m_TextureCoordinate.y
	};
}
