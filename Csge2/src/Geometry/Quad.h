#pragma once

#include<vector>

#include "Transforms.h"
#include "../data/Vertex.h"
#include "../data/IndexedVertexSet.h"


class Quad
{
public:
	Transforms& Transform() { return m_Transform; };

	Quad();

	static IndexedVertexSet* GetVertices();
private:
	Transforms m_Transform;
};
