#include "Quad.h"

Quad::Quad()
{
}

IndexedVertexSet* Quad::GetVertices()
{
	std::vector<Vertex> vertices;

	Vertex v0(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		0);

	Vertex v1(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		1);

	Vertex v2(
		0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		2);

	Vertex v3(
		-0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		3);

	Vertex v4(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		4);

	Vertex v5(
		0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.1f,
		5);

	Vertex v6(
		-0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		6);

	Vertex v7(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		7);

	vertices.push_back(v0);
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);
	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);

	std::vector<unsigned int> indices = {
		/*front*/
		0, 1, 2,
		2, 3, 0,

		/*right*/
		1, 4, 2,
		2, 5, 4,

		/*top*/
		3, 2, 6,
		6, 5, 2,

		/*back*/
		4, 7, 6,
		6, 5, 4,

		/*bottom*/
		7, 4, 1,
		1, 0, 7,

		/*left*/
		7, 0, 3,
		3, 6, 7
	};

	return new IndexedVertexSet(vertices, indices);
}
