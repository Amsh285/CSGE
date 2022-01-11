#pragma once

#include<cmath>
#include<vector>

namespace MathHelper
{
	const double PI = 3.1415926535897932384626433832795;

	float convertToRad(const float& degree);
	double convertToRad(const double& degree);

	std::vector<float> BuildPerspectiveProjectionMatrixGLCenter(float fovy, float aspectRatio, float zNear, float zFar);

	
}