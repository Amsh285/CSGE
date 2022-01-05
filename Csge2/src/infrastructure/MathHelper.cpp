#include "MathHelper.h"

namespace MathHelper
{
	float convertToRad(const float& degree)
	{
		return degree * (PI / 180.0);
	}

	double convertToRad(const double& degree)
	{
		return degree * (PI / 180.0);
	}

	// see https://www.youtube.com/watch?v=U0_ONQQ5ZNM&ab_channel=BrendanGalea
	std::vector<float> BuildPerspectiveProjectionMatrixGLCenter(float fovy, float aspectRatio, float zNear, float zFar)
	{
		float fovyRadHalf = convertToRad(fovy / 2);

		float t = zNear * tan(fovyRadHalf);
		float b = -t;

		float r = t * aspectRatio;
		float l = -r;

		float n = zNear, f = zFar;

		std::vector<float> mat = {
			(2*n)/(r-l), 0, 0, 0,
			0, (2*n)/(t-b), 0, 0,
			(r+l)/(r-l), (t+b)/(t-b), -((f+n)/(f-n)), -1.0f,
			0, 0, -((2*f*n)/(f-n)), 0
		};

		return mat;
	}
}