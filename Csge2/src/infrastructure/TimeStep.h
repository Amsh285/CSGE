#pragma once

class TimeStep
{
public:
	TimeStep(float seconds = 0.0f) : m_Seconds(seconds) {};

	operator float() const { return GetSeconds(); };

	float GetSeconds() const { return m_Seconds; };
	float GetMilliSeconds() const { return m_Seconds * 1000.0f; };
private:
	float m_Seconds;
};