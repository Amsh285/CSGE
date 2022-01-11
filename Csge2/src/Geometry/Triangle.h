#pragma once

#include <string>

#include "../glm/glm/glm.hpp"

class Triangle
{
public:
	glm::vec3 p1, p2, p3;
	glm::vec4 c1, c2, c3;
	glm::vec2 tx1, tx2, tx3;

	void SetTag(const std::string& value) { m_Tag = value; };
	std::string GetTag() const { return m_Tag; };

	Triangle();
	Triangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3
		, const glm::vec4& c1, const glm::vec4& c2, const glm::vec4& c3
		, const glm::vec2& tx1, const glm::vec2& tx2, const glm::vec2& tx3
	);
	
	glm::vec3 GetCentroid() const;
private:
	std::string m_Tag;
};

