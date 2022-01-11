#include "DeltaTime.h"

DeltaTime::DeltaTime()
	: m_LastTime(0.0f)
{
}

TimeStep DeltaTime::GetStepForCurrentFrame()
{
	float elapsedTime = (float)glfwGetTime();
	float deltaTime = elapsedTime - m_LastTime;
	m_LastTime = elapsedTime;

	return TimeStep(deltaTime);
}
