#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

bool loadOBJ(
	const char * path,
	std::vector<float> & out_vertices,
	std::vector<float> & out_uvs,
	std::vector<float> & out_normals,
	std::vector<int> & out_indices
);

#endif
