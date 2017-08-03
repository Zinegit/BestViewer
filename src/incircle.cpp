/**
 * \file incircle.cpp
 * \brief Return incircle of every triangle
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/incircle.hpp"

/**
 * \fn void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius, bool far_plane)
 * \brief This function returns the incircle of each triangle. This function is not currently used by could be in order to simplify the depth culling that is currently to slow to be used.
 *
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param centers : The center of each incircle
 * \param radius : The radius of each incircle
 * \param far_plane : if true, the z coordinate of the center is the same as the far plane's. If not, the z coordiante is the one of the barycenter of the triangle.
 * \return nothing but fills the vectors describing each incircle
 */
void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius, bool far_plane)
{
	for (int i = 0; i < index_triangles.size(); i += 3)
	{
		float a = std::sqrt(std::pow(vertex_positions[3 * index_triangles[i+2]] - vertex_positions[3 * index_triangles[i+1]], 2) + std::pow(vertex_positions[3 * index_triangles[i+2] + 1] - vertex_positions[3 * index_triangles[i+1] + 1], 2) + std::pow(vertex_positions[3 * index_triangles[i+2] + 2] - vertex_positions[3 * index_triangles[i+1] + 2], 2));
		float b = std::sqrt(std::pow(vertex_positions[3 * index_triangles[i]] - vertex_positions[3 * index_triangles[i+2]], 2) + std::pow(vertex_positions[3 * index_triangles[i] + 1] - vertex_positions[3 * index_triangles[i+2] + 1], 2) + std::pow(vertex_positions[3 * index_triangles[i] + 2] - vertex_positions[3 * index_triangles[i+2] + 2], 2));
		float c = std::sqrt(std::pow(vertex_positions[3 * index_triangles[i+1]] - vertex_positions[3 * index_triangles[i]], 2) + std::pow(vertex_positions[3 * index_triangles[i+1] + 1] - vertex_positions[3 * index_triangles[i] + 1], 2) + std::pow(vertex_positions[3 * index_triangles[i+1] + 2] - vertex_positions[3 * index_triangles[i] + 2], 2));
		float s = (a + b + c) / 2;
		float p = (a + b + c);

		centers [i] = (a * vertex_positions[3 * index_triangles[i]] + b * vertex_positions[3 * index_triangles[i+1]] + c * vertex_positions[3 * index_triangles[i+2]]) / p;
		centers [i+1] = (a * vertex_positions[3 * index_triangles[i] + 1] + b * vertex_positions[3 * index_triangles[i+1] + 1] + c * vertex_positions[3 * index_triangles[i+2] + 1]) / p;
		if (far_plane)
			centers [i+2] = (a * vertex_positions[3 * index_triangles[i] + 2] + b * vertex_positions[3 * index_triangles[i+1] + 2] + c * vertex_positions[3 * index_triangles[i+2] + 2]) / p ;
		else {
			std::vector<float> pos (9, 0);
			pos[0] = vertex_positions[3 * index_triangles[i]];
			pos[1] = vertex_positions[3 * index_triangles[i] + 1];
			pos[2] = vertex_positions[3 * index_triangles[i] + 2];
			pos[3] = vertex_positions[3 * index_triangles[i+1]];
			pos[4] = vertex_positions[3 * index_triangles[i+1] + 1];
			pos[5] = vertex_positions[3 * index_triangles[i+1] + 2];
			pos[6] = vertex_positions[3 * index_triangles[i+2]];
			pos[7] = vertex_positions[3 * index_triangles[i+2] + 1];
			pos[8] = vertex_positions[3 * index_triangles[i+2] + 2];

			qglviewer::Vec qgl_bar = barycenter(pos);
			centers[i+2] = qgl_bar[1];
		}
		radius.push_back(std::sqrt(s * (s - a) * (s - b) * (s - c)) / s);
	}
}
