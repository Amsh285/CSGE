#include "Triangle.h"

Triangle::Triangle()
	: Triangle(
		glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec2(0.0f), glm::vec2(1.0f), glm::vec2(1.0f, 1.0f)
	)
{
}

Triangle::Triangle(
	const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
	const glm::vec4& c1, const glm::vec4& c2, const glm::vec4& c3,
	const glm::vec2& tx1, const glm::vec2& tx2, const glm::vec2& tx3)
	: p1(p1), p2(p2), p3(p3),
	c1(c1), c2(c2), c3(c3),
	tx1(tx1), tx2(tx2), tx3(tx3),
	m_Tag("")
{
}

glm::vec3 Triangle::GetCentroid() const
{
	// https://www.lernhelfer.de/schuelerlexikon/mathematik-abitur/artikel/schwerpunkt-eines-dreiecks
	float length = 1.0f / 3.0f;
	return (p1 + p2 + p3) * length;
}

