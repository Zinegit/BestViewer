/**
 * \file notOccultedTriangles.cpp
 * \brief Return a boolean vector representing which triangle is occulted and which is not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/notOccultedTriangles.hpp"

/**
 * \fn std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
 * \brief This function returns a vector of booleans. True is for a triangle visible and false for an occulted triangle. This function is to heavy to run so it is not used here.
 *
 * \param vertex_positions : Geometrical description of the object projected in the near_plane
 * \param vertex_positions_3d : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return Vector of booleans describing which triangle is occulted and which is not
 */
std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
{
	std::vector<float> distances;
	distances.reserve(vertex_positions.size() / 3);
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		float x = vertex_positions[i];
		float y = vertex_positions[i + 1];
		float z = vertex_positions_3d[i + 2];
		qglviewer::Vec point1(x, y, z);
		distances.push_back(distanceToPlane(3, point1, plane_coefficients));
	}
	std::vector<bool> not_occulted_triangles;
	not_occulted_triangles.reserve(index_triangles.size() / 3);
	std::vector<bool> not_occulted_points = notOccultedPoints(vertex_positions, vertex_positions_3d, index_triangles, plane_coefficients, distances);
	for (int i = 0; i < index_triangles.size(); i += 3)
	{
		not_occulted_triangles.push_back(not_occulted_points[index_triangles[i]] || not_occulted_points[index_triangles[i+1]] || not_occulted_points[index_triangles[i+2]]);
	}
	return not_occulted_triangles;
}
