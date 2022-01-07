#pragma once

#include <string>

#include "Transforms.h"

class Geometry
{
public:
	Transforms& Transform() { return m_Transform; };

	const std::string& GetShaderProgram() const { return m_ShaderProgram; };
	const std::string& GetTextureName() const { return m_Texture; };
	const std::string& GetSamplerName() const { return m_SamplerName; };
	const bool& UseTexture() const { return m_UseTexture; };

	Geometry();

	void UseShaderProgram(const std::string& shaderProgram);
	void UseTexture(const std::string& texture, const std::string& shaderProgram);
	void UseTexture(const std::string& texture, const std::string& shaderProgram, const std::string& samplerName);
private:
	Transforms m_Transform;
	std::string m_ShaderProgram;
	std::string m_Texture;
	std::string m_SamplerName;
	bool m_UseTexture;
};
