#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "geometry/Transforms.h"
#include "geometry/Geometry.h"

class RenderingContext
{
public:
	Geometry* GetGeometry() { return m_Geometry; };
	const VertexArray& GetVertexArray() const { return m_VertexArray; };
	const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; };
	ShaderProgram& GetShaderProgram() { return m_ShaderProgram; };

	RenderingContext(Geometry* geometry, VertexArray& va, IndexBuffer& ib, VertexBuffer& vb, ShaderProgram& shaderProgram);

	void Dispose();
private:
	Geometry* m_Geometry;
	VertexArray m_VertexArray;
	IndexBuffer m_IndexBuffer;
	VertexBuffer m_VertexBuffer;
	ShaderProgram m_ShaderProgram;

	bool m_Disposed = false;
};

