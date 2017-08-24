/**
 * \file objLoader.hpp
 * \brief Load the obj. file
 * \author http://www.opengl-tutorial.org/fr / Tom Mourot-Faraut
 * \version 2.0
 */

#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>

#include <glm/glm.hpp>

// To be documented when merged
bool loadOBJ(
	const char * path,
	std::vector<float> & out_vertices,
	std::vector<float> & out_uvs,
	std::vector<float> & out_normals,
	std::vector<int> & out_indices
);

#endif // OBJLOADER_HPP
