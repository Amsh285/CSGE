#pragma once

#include<vector>

#include "Vertex.h"

class IndexedVertexSet
{
public:
	std::vector<Vertex>& GetVertices() { return m_VertexSet; };
	std::vector<unsigned int>& GetIndices() { return m_Indices; };

	IndexedVertexSet(std::vector<Vertex> vertexSet, std::vector<unsigned int> indices);
private:
	std::vector<Vertex> m_VertexSet;
	std::vector<unsigned int> m_Indices;
};

