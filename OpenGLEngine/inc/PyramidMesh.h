#ifndef __PYRAMID_MESH__
#define __PYRAMID_MESH__

#include <vector>
#include "graphics.h"

class PyramidMesh
{
public:
	std::vector<glm::vec3> points;
	std::vector<glm::ivec3> indices;

	PyramidMesh()
	{
		points.push_back(glm::vec3(0.5f, 0.0f, 0.5f));
		points.push_back(glm::vec3(0.5f, 0.0f, -0.5f));
		points.push_back(glm::vec3(-0.5f, 0.0f, -0.5f));
		points.push_back(glm::vec3(-0.5f, 0.0f, 0.5f));
		points.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

		indices.push_back(glm::ivec3(0, 1, 2));
		indices.push_back(glm::ivec3(0, 2, 3));
		indices.push_back(glm::ivec3(0, 1, 4));
		indices.push_back(glm::ivec3(1, 2, 4));
		indices.push_back(glm::ivec3(2, 3, 4));
		indices.push_back(glm::ivec3(3, 0, 4));
	}
};

#endif // !__PYRAMID_MESH__
