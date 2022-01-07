#pragma once

#include <GL/glew.h>

#include "data/Matrix4x4f.h"

#include "IndexBuffer.h"
#include "RenderingContext.h"
#include "ShaderProgram.h"
#include "Utility.h"
#include "VertexArray.h"

class Renderer
{
public:
	const Matrix4x4f GetPerspective() const { return m_Perspective; };
	void SetPerspective(float fovy, float aspectRatio, float zNear, float zFar);
	void SetPerspective(Matrix4x4f& mvp);

	Renderer();

	void Clear();
	void Draw(RenderingContext& context);
	void Draw(Transforms& transform, const VertexArray& va, const IndexBuffer& ib, ShaderProgram& shaderProgram);

	~Renderer();
private:
	Matrix4x4f m_Perspective;
};
