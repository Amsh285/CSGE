#include "RenderingContext.h"

RenderingContext::RenderingContext(Geometry& geometry, VertexArray& va, IndexBuffer& ib, VertexBuffer& vb, ShaderProgram& shaderProgram)
	: m_Geometry(geometry), m_VertexArray(va), m_IndexBuffer(ib), m_VertexBuffer(vb), m_ShaderProgram(shaderProgram), m_Disposed(false)
{
}

void RenderingContext::Dispose()
{
	/*if (!m_Disposed)
	{
		m_VertexArray.Dispose();
		m_IndexBuffer.Dispose();
		m_VertexBuffer.Dispose();
		m_ShaderProgram.DeleteProgram();
	}*/
}
