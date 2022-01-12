#include "DeltaTime.h"

DeltaTime::DeltaTime()
	: m_LastTime(0.0f), m_CurrentTime(0.0f)
{
}

void DeltaTime::Update()
{
	float elapsedTime = (float)glfwGetTime();
	m_LastTime = m_CurrentTime;
	m_CurrentTime = elapsedTime;
}

TimeStep DeltaTime::GetStepForCurrentFrame()
{
	return TimeStep(m_CurrentTime - m_LastTime);
}
