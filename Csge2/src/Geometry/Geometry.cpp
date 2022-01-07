#include "Geometry.h"

Geometry::Geometry()
	: m_ShaderProgram("default"), m_Texture(""), m_SamplerName(""), m_UseTexture(false)
{
}

void Geometry::UseShaderProgram(const std::string& shaderProgram)
{
	m_ShaderProgram = shaderProgram;
}

void Geometry::UseTexture(const std::string& texture, const std::string& shaderProgram)
{
	UseTexture(texture, shaderProgram, "tex1");
}

void Geometry::UseTexture(const std::string& texture, const std::string& shaderProgram, const std::string& samplerName)
{
	m_UseTexture = true;
	m_Texture = texture;
	m_SamplerName = samplerName;

	UseShaderProgram(shaderProgram);
}
