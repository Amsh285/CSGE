#include "Utility.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}

	return true;
}

namespace Utility
{
	std::string Utility::ReadTextFile(const char* fileName)
	{
		std::string temp;
		std::string result;
		std::ifstream stream(fileName);

		while (std::getline(stream, temp))
		{
			result += temp;
			result += '\n';
		}

		stream.close();

		return result;
	}
}


