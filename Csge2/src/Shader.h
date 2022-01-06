#pragma once

#include<iostream>
#include<string>

#include "GL/glew.h"
#include "Utility.h"

//Todo: Delete Copy Ctor. add move ctor etc...
class Shader
{
public:
	const std::string& GetSourceCode() const { return m_SourceCode; };

	const unsigned int& GetShaderType() const { return m_ShaderType; };

	const std::string& GetName() const { return m_Name; };

	const unsigned int& GetShaderID() const { return m_ShaderID; };

	const bool& IsCompiled() const { return m_IsCompiled; };

	Shader(const std::string& sourceCode, const unsigned int& shaderType, const std::string& name);

	static Shader LoadFromFile(const char* fileName, const unsigned int& shaderType, const std::string& name);

	void Compile();
	void DeleteShader();

	~Shader();
private:
	const std::string m_SourceCode;
	const unsigned int m_ShaderType;
	const std::string m_Name;

	unsigned int m_ShaderID;

	bool m_IsCompiled = false;
};

