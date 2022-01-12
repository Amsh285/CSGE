#include "Quad.h"

Quad::Quad()
{
}

IndexedVertexSet* Quad::GetVerticesLoD()
{
	std::vector<Vertex> vertices;

	/*front side*/
	Vertex v1(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		0
	);

	Vertex v2(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		1
	);

	Vertex v3(
		0.0f, 0.5f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 1.0f,
		2
	);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	/*right side*/
	Vertex v4(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		3
	);

	Vertex v5(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		4
	);

	vertices.push_back(v4);
	vertices.push_back(v5);

	/*left side*/
	Vertex v6(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		5
	);

	Vertex v7(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		6
	);

	vertices.push_back(v6);
	vertices.push_back(v7);

	/*back side*/
	Vertex v8(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		7
	);

	Vertex v9(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		8
	);

	vertices.push_back(v8);
	vertices.push_back(v9);

	/*bottom square*/
	Vertex v10(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		9
	);

	Vertex v11(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		10
	);

	Vertex v12(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		11
	);

	Vertex v13(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		12
	);

	vertices.push_back(v10);
	vertices.push_back(v11);
	vertices.push_back(v12);
	vertices.push_back(v13);

	std::vector<unsigned int> indices{
		/*front side*/
		v1.GetIndex(), v2.GetIndex(), v3.GetIndex(),
		/*right side*/
		v4.GetIndex(), v5.GetIndex(), v3.GetIndex(),
		/*left side*/
		v6.GetIndex(), v7.GetIndex(), v3.GetIndex(),
		/*back side*/
		v8.GetIndex(), v9.GetIndex(), v3.GetIndex(),
		/*bottom square*/
		v10.GetIndex(),  v11.GetIndex(), v12.GetIndex(),
		v12.GetIndex(), v13.GetIndex(), v10.GetIndex()
	};

	return new IndexedVertexSet(vertices, indices);
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

IndexedVertexSet* Quad::GetVertices24()
{
	/* Front */
	std::vector<Vertex> vertices;

	Vertex v1(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		0
	);

	Vertex v2(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		1
	);

	Vertex v3(
		0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		2
	);

	Vertex v4(
		-0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		3
	);

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
	vertices.push_back(v4);

	/* Right */
	Vertex v5(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		4
	);

	Vertex v6(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		5
	);

	Vertex v7(
		0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		6
	);

	Vertex v8(
		0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		7
	);

	vertices.push_back(v5);
	vertices.push_back(v6);
	vertices.push_back(v7);
	vertices.push_back(v8);

	/* left */
	Vertex v9(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		8
	);


	Vertex v10(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		9
	);

	Vertex v11(
		-0.5, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		10
	);

	Vertex v12(
		-0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		11
	);

	vertices.push_back(v9);
	vertices.push_back(v10);
	vertices.push_back(v11);
	vertices.push_back(v12);

	/* back */
	Vertex v13(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		12
	);

	Vertex v14(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		13
	);

	Vertex v15(
		-0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		14
	);

	Vertex v16(
		0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		15
	);

	vertices.push_back(v13);
	vertices.push_back(v14);
	vertices.push_back(v15);
	vertices.push_back(v16);

	/* bottom */
	Vertex v17(
		0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		16
	);

	Vertex v18(
		-0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		17
	);

	Vertex v19(
		-0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		18
	);

	Vertex v20(
		0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		19
	);

	vertices.push_back(v17);
	vertices.push_back(v18);
	vertices.push_back(v19);
	vertices.push_back(v20);

	/* top */
	Vertex v21(
		-0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		20
	);

	Vertex v22(
		0.5f, 0.5f, 0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f,
		21
	);

	Vertex v23(
		0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		22
	);

	Vertex v24(
		-0.5f, 0.5f, -0.5f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		23
	);

	vertices.push_back(v21);
	vertices.push_back(v22);
	vertices.push_back(v23);
	vertices.push_back(v24);

	std::vector<unsigned int> indices {
		/*front side*/
		0, 1, 2,
		2, 3, 0,

		/*right side*/
		4, 5, 6,
		6, 7, 4,

		/*left side*/
		8, 9, 10,
		10, 11, 8,

		/*back side*/
		12, 13, 14,
		14, 15, 12,

		/*bottom side*/
		16, 17, 18,
		18, 19, 16,

		/*up side*/
		20, 21, 22,
		22, 23, 20
	};

	return new IndexedVertexSet(vertices, indices);
}
