#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "graphics.h"

class Mesh
{
public:
	std::vector<glm::vec3> points;
	std::vector<glm::ivec3> indices;

public:
	Mesh()
	{}

protected:
	virtual void initialize() = 0;
};

#endif // !__MESH__
