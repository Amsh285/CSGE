#pragma once

#include "Utility.h"

class VertexBuffer 
{
public:
	VertexBuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;

	void Dispose();

	~VertexBuffer();
private:
	unsigned int m_RendererID;
	bool m_Disposed;
};