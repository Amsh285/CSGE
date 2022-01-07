#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "geometry/Transforms.h"

class RenderingContext
{
public:
	Transforms& GetTransform() { return m_Transform; };
	const VertexArray& GetVertexArray() const { return m_VertexArray; };
	const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; };
	ShaderProgram& GetShaderProgram() { return m_ShaderProgram; };

	RenderingContext(Transforms& transform, const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shaderProgram);
private:
	Transforms m_Transform;
	const VertexArray m_VertexArray;
	const IndexBuffer m_IndexBuffer;
	ShaderProgram m_ShaderProgram;
};

