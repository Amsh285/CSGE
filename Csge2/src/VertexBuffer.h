#pragma once

#include "Utility.h"

class VertexBuffer 
{
public:
	VertexBuffer(const void* data, unsigned int size);

	void Bind() const;
	void Unbind() const;

	~VertexBuffer();
private:
	unsigned int m_RendererID;
};