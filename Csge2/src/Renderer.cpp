#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const RenderingContext& context)
{
	Draw(context.GetVertexArray(), context.GetIndexBuffer(), context.GetShaderProgram());
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shaderProgram)
{
	va.Bind();
	ib.Bind();
	shaderProgram.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

Renderer::~Renderer()
{
}
