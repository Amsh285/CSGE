#include "Shader.h"

Shader::Shader(const std::string& sourceCode, const unsigned int& shaderType, const std::string& name)
	: m_SourceCode(sourceCode), m_ShaderType(shaderType), m_Name(name), m_ShaderID(0)
{
}

Shader Shader::LoadFromFile(const char* fileName, const unsigned int& shaderType, const std::string& name)
{
	const std::string sourceCode = Utility::ReadTextFile(fileName);
	return Shader(sourceCode, shaderType, name);
}

void Shader::Compile()
{
	m_ShaderID = glCreateShader(m_ShaderType);
	const char* src = m_SourceCode.c_str();

	GLCall(glShaderSource(m_ShaderID, 1, &src, nullptr));
	GLCall(glCompileShader(m_ShaderID));

	int result;
	GLCall(glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));

		GLCall(glGetShaderInfoLog(m_ShaderID, length, &length, message));

		std::cout << "failed to compile shader: " << m_Name << std::endl;
		std::cout << message << std::endl;

		GLCall(glDeleteShader(m_ShaderID));
		m_ShaderID = 0;
	}

	m_IsCompiled = true;
}

void Shader::DeleteShader()
{
	GLCall(glDeleteShader(m_ShaderID));
	m_IsCompiled = false;
}

Shader::~Shader()
{
	if (m_IsCompiled)
		DeleteShader();
}