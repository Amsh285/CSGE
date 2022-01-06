#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const std::vector<VertexBufferLayoutElement>& elements = layout.GetElements();
	unsigned int offset = 0;

	for (size_t i = 0; i < elements.size(); i++)
	{
		const VertexBufferLayoutElement& currentElement = elements.at(i);

		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, currentElement.Count, currentElement.Type, currentElement.Normalized, layout.GetStride(), (const void*)offset));

		offset += currentElement.Count * VertexBufferLayoutElement::GetSizeOfType(currentElement.Type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}

VertexArray::~VertexArray()
{
	/*GLCall(glDeleteVertexArrays(1, &m_RendererID));*/
}
