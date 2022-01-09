#pragma once

#include <ostream>
#include <string>


struct MousePosition
{
	double X;
	double Y;

	MousePosition() : MousePosition(0.0, 0.0) {}

	MousePosition(double x, double y)
		: X(x), Y(y)
	{
	}

	friend std::ostream& operator<< (std::ostream& stream, const MousePosition& position)
	{
		return stream << "position x: " << position.X << " y: " << position.Y;
	}
};