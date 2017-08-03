/**
 * \file projection.cpp
 * \brief Return the coordinates of the triangles projected on the near plane
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/projection.hpp"

/**
 * \fn std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane)
 * \brief This function projects every vertex in the near/far plane
 *
 * \param vertex_positions : Geometrical description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \param nb_plane : 0 -> 5 describes which plane of the frustum is used (3 or 4 should be used because they represent the near and far planes)
 * \return vertex_positions with the z coordinate of every vertex being the z coordinate of the near/far plane
 */
std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane)
{
	std::vector<float> projected_vertex_positions;
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		float a = plane_coefficients[nb_plane][0];
		float b = plane_coefficients[nb_plane][1];
		float c = plane_coefficients[nb_plane][2];
		float d = plane_coefficients[nb_plane][3];
		float u = vertex_positions[i];
		float v = vertex_positions[i+1];
		float w = vertex_positions[i+2];
		projected_vertex_positions.push_back(u - a * (a * u + b * v + c * w + d) / (std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2)));
		projected_vertex_positions.push_back(v - b * (a * u + b * v + c * w + d) / (std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2)));
		projected_vertex_positions.push_back(w - c * (a * u + b * v + c * w + d) / (std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2)));
	}
	return projected_vertex_positions;
}
