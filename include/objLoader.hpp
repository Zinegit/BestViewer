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

bool loadOBJ(const char * path,
	std::vector<float>& vertices_in_order,
	std::vector<float>& uvs_in_order,
	std::vector<float> &normals_in_order,
	std::vector<float> &out_vertices,
	std::vector<int> &out_indices);

bool is_near(float v1, float v2);

bool getSimilarVertexIndex(std::vector<float> &in_vertex,
	std::vector<float> &in_uv,
	std::vector<float> &in_normal,
	std::vector<float> &out_vertices,
	std::vector<float> &out_uvs,
	std::vector<float> &out_normals,
	int &index);

void indexVBO(std::vector<float> &in_vertices,
	std::vector<float> &in_uvs,
	std::vector<float> &in_normals,
	std::vector<int> &out_indices,
	std::vector<float> &out_vertices,
	std::vector<float> &out_uvs,
	std::vector<float> &out_normals);


#endif // OBJLOADER_HPP
