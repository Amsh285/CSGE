#pragma once

#include <string>

#include "GL/glew.h"

#include "../Utility.h"
#include "../vendor/stb_image/stb_image.h"

class Texture
{
public:
	int GetWidth() const { return m_Width; };
	int GetHeight() const { return m_Height; };

	unsigned int GetRendererID() const { return m_RendererID; };

	Texture(const std::string& path);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	~Texture();
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

