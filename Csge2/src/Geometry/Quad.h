#pragma once

#include<vector>

#include "Geometry.h"
#include "Transforms.h"
#include "../data/Vertex.h"
#include "../data/IndexedVertexSet.h"


class Quad : public Geometry
{
public:
	Quad();

	static IndexedVertexSet* GetVertices();
private:
	Transforms m_Transform;
};
