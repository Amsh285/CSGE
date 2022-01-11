#include "IndexedVertexSet.h"

IndexedVertexSet::IndexedVertexSet(const std::vector<Vertex>& vertexSet, const std::vector<unsigned int>& indices)
	: m_VertexSet(vertexSet), m_Indices(indices)
{
}
