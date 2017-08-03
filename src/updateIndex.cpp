/**
 * \file updateIndex.cpp
 * \brief Fill the triangle indices vector with the triangles supposed to be drawn
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/updateIndex.hpp"

/**
 * \fn std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index)
 * \brief This function updates the index_triangles vector in order to select only the ones that are supposed to be drawn
 *
 * \param triangles_to_show : Vector of booleans describing which triangle is supposed to be drawn
 * \param index : Topological description of the object
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
