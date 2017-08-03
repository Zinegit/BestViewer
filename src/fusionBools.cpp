/**
 * \file fusionBools.cpp
 * \brief Return the vector of every triangle that is to be drawn
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/fusionBools.hpp"

/**
 * \fn std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles)
 * \brief This function returns a vector that verifies that each triangle is both frontface and inside the frustum
 *
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


