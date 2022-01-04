#pragma once

#include <vector>

#include "GL/glew.h"

#include "Shader.h"
#include "Utility.h"

class ShaderProgram
{
public:
	const unsigned int& GetProgramID() const { return m_RendererID; };

	ShaderProgram(std::vector<std::unique_ptr<Shader>>& shaders);

	void Build();

	void Bind();

	void Unbind();

	void DeleteProgram();

	~ShaderProgram();
private:
	unsigned int m_RendererID;

	std::vector<std::unique_ptr<Shader>>& m_Shaders;
};

