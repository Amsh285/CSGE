#pragma once

#include <iostream>
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
	void Bind() const;
	void Unbind() const;
	void DeleteProgram();

	void SetUniformMat4f(const std::string& name, float* mat);

	~ShaderProgram();
private:
	int GetUniformLocation(const std::string& name);

	unsigned int m_RendererID;

	std::vector<std::unique_ptr<Shader>>& m_Shaders;
};

