#ifndef __CUBE_MESH_H__
#define __CUBE_MESH_H__

#include "Mesh.h"

class CubeMesh : public Mesh
{
public:
	CubeMesh()
	{
		initialize();
	}

	void initialize() override
	{
		points.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));
		points.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));
		points.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));
		points.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));
		
		points.push_back(glm::vec3( 0.5f, 0.5f,  0.5f));
		points.push_back(glm::vec3( 0.5f, 0.5f, -0.5f));
		points.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));
		points.push_back(glm::vec3(-0.5f, 0.5f,  0.5f));

		indices.push_back(glm::ivec3(0, 1, 2));
		indices.push_back(glm::ivec3(0, 2, 3));
		
		indices.push_back(glm::ivec3(4, 5, 6));
		indices.push_back(glm::ivec3(4, 6, 7));

		indices.push_back(glm::ivec3(0, 1, 5));
		indices.push_back(glm::ivec3(0, 4, 5));
		
		indices.push_back(glm::ivec3(1, 2, 5));
		indices.push_back(glm::ivec3(2, 5, 6));
	
		indices.push_back(glm::ivec3(2, 3, 7));
		indices.push_back(glm::ivec3(2, 6, 7));

		indices.push_back(glm::ivec3(0, 3, 4));
		indices.push_back(glm::ivec3(3, 4, 7));
	}
};

#endif // !__CUBE_MESH__
