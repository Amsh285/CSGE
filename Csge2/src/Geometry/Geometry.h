#pragma once

#include "Transforms.h"

class Geometry
{
public:
	Transforms& Transform() { return m_Transform; };

	Geometry();

private:
	Transforms m_Transform;
};

