#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::vector<std::unique_ptr<Shader>>& shaders)
	: m_Shaders(shaders), m_RendererID(0)
{
}

void ShaderProgram::Build()
{
	m_RendererID = glCreateProgram();

	for (size_t i = 0; i < m_Shaders.size(); i++)
	{
		std::unique_ptr<Shader>& shader = m_Shaders.at(i);

		if (!shader->IsCompiled())
			shader->Compile();

		GLCall(glAttachShader(m_RendererID, shader->GetShaderID()));
	}

	GLCall(glLinkProgram(m_RendererID));
	GLCall(glValidateProgram(m_RendererID));

	for (size_t i = 0; i < m_Shaders.size(); i++)
		m_Shaders.at(i)->DeleteShader();
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
	GLCall(glDeleteProgram(m_RendererID));
	m_RendererID = 0;
}

void ShaderProgram::SetUniformMat4f(const std::string& name, float* mat)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, false, mat));
}

ShaderProgram::~ShaderProgram()
{
	Unbind();
	DeleteProgram();
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	 GLCall(int result = glGetUniformLocation(m_RendererID, name.c_str()));

	if (result == -1)
		std::cout << "Error: Uniform: " << name << " not found." << std::endl;

	return result;
}
