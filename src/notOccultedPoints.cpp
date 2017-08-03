/**
 * \file notOccultedPoints.cpp
 * \brief Return a boolean vector representing which point is occulted and which is not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/notOccultedPoints.hpp"

/**
 * \fn std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances)
 * \brief This function returns a vector of booleans. True is for a point visible and false for an occulted point. This function is to heavy to run so it is not used here.
 *
 * \param vertex_positions : Geometrical description of the object projected in the near_plane
 * \param vertex_positions_3d : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \param distances : The distances of every vertex from the near plane
 * \return Vector of booleans describing which point is occulted and which is not
 */
std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances)
{
	std::vector<bool> not_occulted_points;
	not_occulted_points.reserve(vertex_positions.size() / 3);
	int j = 0;
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		std::vector<float> point;
		point.push_back(vertex_positions[i]);
		point.push_back(vertex_positions[i+1]);
		point.push_back(vertex_positions_3d[i+2]);
		float d4 = distances[j];
		not_occulted_points.push_back(isNotOcculted(vertex_positions, vertex_positions_3d, index_triangles, point, j, plane_coefficients, distances, d4));
		j += 1;
	}
	return not_occulted_points;
}
