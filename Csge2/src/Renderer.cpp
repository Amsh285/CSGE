#include "Renderer.h"

Renderer::Renderer()
	: m_Perspective_glm_Test(nullptr)
{
}

void Renderer::SetPerspective(float fovy, float aspectRatio, float zNear, float zFar)
{
	m_Perspective =  Matrix4x4f::Perspective(fovy, aspectRatio, zNear, zFar);
}

void Renderer::SetPerspective(Matrix4x4f& mvp)
{
	m_Perspective = mvp;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(RenderingContext& context, std::map<std::string, Texture*> textures)
{
	Draw(context.GetGeometry(), context.GetVertexArray(), context.GetIndexBuffer(), context.GetShaderProgram(), textures);
}

void Renderer::Draw(Geometry* geometry, const VertexArray& va, const IndexBuffer& ib, ShaderProgram& shaderProgram, std::map<std::string, Texture*> textures)
{
	va.Bind();
	ib.Bind();
	shaderProgram.Bind();
	
	std::vector<float> mvp = m_Perspective.GetOpenGlRepresentation();

	Matrix4x4f transformations = geometry->Transform().GetTransformationMatrix();
	std::vector<float> v_Transform = transformations.GetOpenGlRepresentation();

	/*shaderProgram.SetUniformMat4f("u_MVP", &mvp[0]);*/
	shaderProgram.SetUniformMat4f("u_MVP", m_Perspective_glm_Test);
	shaderProgram.SetUniformMat4f("u_Transform", &v_Transform[0]);
	
	if (geometry->UseTexture())
	{
		Texture* tex = textures[geometry->GetTextureName()];
		tex->Bind(0);

		shaderProgram.SetUniform1i(geometry->GetSamplerName(), 0);
	}

 	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

Renderer::~Renderer()
{
}
