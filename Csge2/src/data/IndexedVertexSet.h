#pragma once

#include<vector>

#include "Vertex.h"

class IndexedVertexSet
{
public:
	const std::vector<Vertex>& GetVertices() const { return m_VertexSet; };
	const std::vector<unsigned int>& GetIndices() const { return m_Indices; };

	IndexedVertexSet(const std::vector<Vertex>& vertexSet, const std::vector<unsigned int>& indices);
private:
	std::vector<Vertex> m_VertexSet;
	std::vector<unsigned int> m_Indices;
};

