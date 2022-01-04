#pragma once

#include <GL/glew.h>

#include "IndexBuffer.h"
#include "RenderingContext.h"
#include "ShaderProgram.h"
#include "Utility.h"
#include "VertexArray.h"

class Renderer
{
public:
	Renderer();

	void Clear();
	void Draw(const RenderingContext& context);
	void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& shaderProgram);

	~Renderer();
private:
};
