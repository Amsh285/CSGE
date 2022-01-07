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

	ShaderProgram(const std::vector<Shader>& shaders);

	void Build();
	void Bind() const;
	void Unbind() const;
	void DeleteProgram();

	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, float* mat);
private:
	int GetUniformLocation(const std::string& name);

	unsigned int m_RendererID;

	std::vector<Shader> m_Shaders;

	bool m_Deleted;
};

