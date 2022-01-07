#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::vector<Shader>& shaders)
	: m_Shaders(shaders), m_RendererID(0), m_Deleted(false)
{
}

void ShaderProgram::Build()
{
	m_RendererID = glCreateProgram();

	for (size_t i = 0; i < m_Shaders.size(); i++)
	{
		Shader& shader = m_Shaders.at(i);
		GLCall(glAttachShader(m_RendererID, shader.GetShaderID()));
	}

	GLCall(glLinkProgram(m_RendererID));
	GLCall(glValidateProgram(m_RendererID));
}

void ShaderProgram::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void ShaderProgram::Unbind() const
{
	GLCall(glUseProgram(0));
}

void ShaderProgram::DeleteProgram()
{
	if (!m_Deleted)
	{
		GLCall(glDeleteProgram(m_RendererID));
		m_RendererID = 0;
		m_Deleted = true;
	}
}

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void ShaderProgram::SetUniformMat4f(const std::string& name, float* mat)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, false, mat));
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	 GLCall(int result = glGetUniformLocation(m_RendererID, name.c_str()));

	if (result == -1)
		std::cout << "Error: Uniform: " << name << " not found." << std::endl;

	return result;
}
