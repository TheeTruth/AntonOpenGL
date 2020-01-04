#pragma once
#include <vector>
#include <glm/glm.hpp>

class Model
{
public:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
};