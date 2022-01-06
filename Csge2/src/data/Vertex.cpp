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

std::vector<float> Vertex::GetVertexBuffer()
{
	return std::vector<float>{
		m_Position.X(), m_Position.Y(), m_Position.Z(),
		m_Color.X(), m_Color.Y(), m_Color.Z(), m_Color.H(),
		m_TextureCoordinate.x, m_TextureCoordinate.y
	};
}
