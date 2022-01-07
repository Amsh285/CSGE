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

	RenderingContext(Transforms& transform, VertexArray& va, IndexBuffer& ib, VertexBuffer& vb, ShaderProgram& shaderProgram);

	void Dispose();
private:
	Transforms m_Transform;
	VertexArray m_VertexArray;
	IndexBuffer m_IndexBuffer;
	VertexBuffer m_VertexBuffer;
	ShaderProgram m_ShaderProgram;

	bool m_Disposed = false;
};

