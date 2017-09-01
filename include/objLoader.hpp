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

/**
 * \fn bool loadOBJ(const char *path, std::vector<float>& vertices, std::vector<float>& uvs, std::vector<float> &normals);
 * \brief This function loads the object file
 * \param path : The path to the file
 * \param vertices : Geometrical description of the object
 * \param uvs : UV coordinates (see http://www.opengl-tutorial.org/fr/beginners-tutorials/tutorial-5-a-textured-cube/)
 * \param normals : The normal of each face
 * \return A boolean being true if the object file is loaded
 */
bool loadOBJ(const char *path,
	std::vector<float>& vertices,
	std::vector<float>& uvs,
	std::vector<float>& normals);

/**
 * \fn bool is_near(float v1, float v2);
 * \brief This compares two floats
 * \param v1 : first float
 * \param v2 : second float
 * \return A boolean being true if the two floats are more or less the same value
 */
bool is_near(float v1, float v2);

/**
 * \fn bool getSimilarVertexIndex(std::vector<float> &in_vertex, std::vector<float> &in_uv, std::vector<float> &in_normal, std::vector<float> &out_vertices, std::vector<float> &out_uvs, std::vector<float> &out_normals, int &index);
 * \brief This function checks if the vertex described by in_vertex and in_uv is already in the list of vertices that will be used (The normal is not used here)
 * \param in_vertex : The input vertex
 * \param in_uv : The input uv coordinates
 * \param in_normal : The input normal
 * \param out_vertices : The output list of vertices
 * \param out_uvs : The output list of uv coordinates
 * \param out_normals : The output list of normals
 * \return A boolean being true if the input vertex is already in the list
 */
bool getSimilarVertexIndex(std::vector<float> &in_vertex,
	std::vector<float> &in_uv,
	std::vector<float> &in_normal,
	std::vector<float> &out_vertices,
	std::vector<float> &out_uvs,
	std::vector<float> &out_normals,
	int &index);

/**
 * \fn void indexVBO(std::vector<float> &in_vertices, std::vector<float> &in_uvs, std::vector<float> &in_normals, std::vector<int> &out_indices, std::vector<float> &out_vertices, std::vector<float> &out_uvs, std::vector<float> &out_normals);
 * \brief This function checks for a double vertex in the lists and returns a list of indices so that no vertex can be found two times
 * \param in_vertices : The input vertices
 * \param in_uvs : The input uv coordinates
 * \param in_normals : The input normals
 * \param out_indices : The output indices
 * \param out_vertices : The output list of vertices
 * \param out_uvs : The output list of uv coordinates
 * \param out_normals : The output list of normals
 * \return void
 */
void indexVBO(std::vector<float> &in_vertices,
	std::vector<float> &in_uvs,
	std::vector<float> &in_normals,
	std::vector<int> &out_indices,
	std::vector<float> &out_vertices,
	std::vector<float> &out_uvs,
	std::vector<float> &out_normals);


#endif // OBJLOADER_HPP
