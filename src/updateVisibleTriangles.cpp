/**
 * \file updateVisibleTriangles.cpp
 * \brief These functions are used to udpate the triangles to show according to the differents cullings that have been used
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/updateVisibleTriangles.hpp"

/**
 * \fn std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles)
 * \brief This function returns a vector that verifies that each triangle is both frontface and inside the frustum
 * \param front_face_triangles : Triangles that are oriented towards the viewer
 * \param inside_frustum_triangles : Triangles that are inside the frustum
 * \return A vector of booleans representing triangles that are both frontface and inside the frustum
 */
std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles)
{
	std::vector<bool> fusion;
	fusion.reserve(front_face_triangles.size());
	for (int i = 0; i < front_face_triangles.size(); i++)
	{
		fusion.push_back(front_face_triangles[i] && inside_frustum_triangles[i]);
	}
	return fusion;
}

/**
 * \fn std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index)
 * \brief This function updates the index_triangles vector in order to select only the ones that are supposed to be drawn
 * \param triangles_to_show : Vector of booleans describing which triangle is supposed to be drawn
 * \param index_triangles : Topological description of the object
 * \return New index_triangles containing only the triangles to draw
 */
std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index_triangles)
{
	std::vector<int> new_index;
	for (int i = 0; i < triangles_to_show.size(); i++)
	{
		if (triangles_to_show[i])
		{
			new_index.push_back(index_triangles[3 * i]);
			new_index.push_back(index_triangles[3 * i + 1]);
			new_index.push_back(index_triangles[3 * i + 2]);
		}
	}
	return new_index;
}
