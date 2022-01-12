#pragma once

#include "GLFW/glfw3.h"
#include "TimeStep.h"

class DeltaTime
{
public:
	DeltaTime();

	void Update();
	TimeStep GetStepForCurrentFrame();
private:
	float m_LastTime, m_CurrentTime;
};

