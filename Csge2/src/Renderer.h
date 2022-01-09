#pragma once

#include<map>

#include <GL/glew.h>

#include "data/Matrix4x4f.h"
#include "data/Texture.h"

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

	void SetPerspectivef(float* glm_test) { m_Perspective_glm_Test = glm_test; };

	Renderer();

	void Clear();
	void Draw(RenderingContext& context, std::map<std::string, Texture*> textures);
	void Draw(Geometry& geometry, const VertexArray& va, const IndexBuffer& ib, ShaderProgram& shaderProgram, std::map<std::string, Texture*> textures);

	~Renderer();
private:
	Matrix4x4f m_Perspective;
	float* m_Perspective_glm_Test;
};
