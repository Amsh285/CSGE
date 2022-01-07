#pragma once

#include "Utility.h"

class IndexBuffer
{
public:
	inline unsigned int GetCount() const { return m_Count; }

	IndexBuffer(const unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	void Dispose();

	~IndexBuffer();
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
	bool m_Disposed;
};