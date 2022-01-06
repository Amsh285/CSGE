#include "IndexedVertexSet.h"

IndexedVertexSet::IndexedVertexSet(std::vector<Vertex> vertexSet, std::vector<unsigned int> indices)
	: m_VertexSet(vertexSet), m_Indices(indices)
{
}
