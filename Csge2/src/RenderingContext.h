#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"

class RenderingContext
{
public:
	inline const VertexArray& GetVertexArray() const { return m_VertexArray; };
	inline const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; };
	inline const ShaderProgram& GetShaderProgram() const { return m_ShaderProgram; };

	RenderingContext(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shaderProgram);
private:
	const VertexArray& m_VertexArray;
	const IndexBuffer& m_IndexBuffer;
	const ShaderProgram& m_ShaderProgram;
};

