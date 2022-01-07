#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_Disposed(false)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Dispose()
{
	if (!m_Disposed)
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
		m_Disposed = true;
	}
}

VertexBuffer::~VertexBuffer()
{
	/*GLCall(glDeleteBuffers(1, &m_RendererID));*/
}
