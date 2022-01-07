#pragma once

#include "Utility.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

	void Dispose();

	~VertexArray();
private:
	unsigned int m_RendererID;
	bool m_Disposed;
};