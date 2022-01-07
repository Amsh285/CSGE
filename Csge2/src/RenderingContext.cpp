#include "RenderingContext.h"

RenderingContext::RenderingContext(Transforms& transform, const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shaderProgram)
	: m_Transform(transform), m_VertexArray(va), m_IndexBuffer(ib), m_ShaderProgram(shaderProgram)
{
}
