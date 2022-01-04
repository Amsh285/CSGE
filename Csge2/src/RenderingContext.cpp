#include "RenderingContext.h"

RenderingContext::RenderingContext(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shaderProgram)
	: m_VertexArray(va), m_IndexBuffer(ib), m_ShaderProgram(shaderProgram)
{
}
