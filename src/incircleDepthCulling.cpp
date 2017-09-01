#include "include/incircleDepthCulling.hpp"

std::vector<float> project(std::vector<float>& vertices, GLdouble plane_coefficients[6][4], int nb_plane)
{
	std::vector<float> projected_vertex_positions;
	for (int i = 0; i < vertices.size(); i += 3)
	{
		float a = plane_coefficients[nb_plane][0];
		float b = plane_coefficients[nb_plane][1];
		float c = plane_coefficients[nb_plane][2];
		float d = plane_coefficients[nb_plane][3];
		float u = vertices[i];
		float v = vertices[i+1];
		float w = vertices[i+2];
		projected_vertex_positions.push_back(u - a * (a * u + b * v + c * w + d) / (std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2)));
		projected_vertex_positions.push_back(v - b * (a * u + b * v + c * w + d) / (std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2)));
		projected_vertex_positions.push_back(w - c * (a * u + b * v + c * w + d) / (std::pow(a, 2) + std::pow(b, 2) + std::pow(c, 2)));
	}
	return projected_vertex_positions;
}

void incircle (std::vector<float>& vertices, std::vector<int>& indices, std::vector<float>& centers, std::vector<float>& radius, bool far_plane)
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		float a = std::sqrt(std::pow(vertices[3 * indices[i+2]] - vertices[3 * indices[i+1]], 2) + std::pow(vertices[3 * indices[i+2] + 1] - vertices[3 * indices[i+1] + 1], 2) + std::pow(vertices[3 * indices[i+2] + 2] - vertices[3 * indices[i+1] + 2], 2));
		float b = std::sqrt(std::pow(vertices[3 * indices[i]] - vertices[3 * indices[i+2]], 2) + std::pow(vertices[3 * indices[i] + 1] - vertices[3 * indices[i+2] + 1], 2) + std::pow(vertices[3 * indices[i] + 2] - vertices[3 * indices[i+2] + 2], 2));
		float c = std::sqrt(std::pow(vertices[3 * indices[i+1]] - vertices[3 * indices[i]], 2) + std::pow(vertices[3 * indices[i+1] + 1] - vertices[3 * indices[i] + 1], 2) + std::pow(vertices[3 * indices[i+1] + 2] - vertices[3 * indices[i] + 2], 2));
		float s = (a + b + c) / 2;
		float p = (a + b + c);

		centers [i] = (a * vertices[3 * indices[i]] + b * vertices[3 * indices[i+1]] + c * vertices[3 * indices[i+2]]) / p;
		centers [i+1] = (a * vertices[3 * indices[i] + 1] + b * vertices[3 * indices[i+1] + 1] + c * vertices[3 * indices[i+2] + 1]) / p;
		if (far_plane)
			centers [i+2] = (a * vertices[3 * indices[i] + 2] + b * vertices[3 * indices[i+1] + 2] + c * vertices[3 * indices[i+2] + 2]) / p ;
		else {
			std::vector<float> pos (9, 0);
			pos[0] = vertices[3 * indices[i]];
			pos[1] = vertices[3 * indices[i] + 1];
			pos[2] = vertices[3 * indices[i] + 2];
			pos[3] = vertices[3 * indices[i+1]];
			pos[4] = vertices[3 * indices[i+1] + 1];
			pos[5] = vertices[3 * indices[i+1] + 2];
			pos[6] = vertices[3 * indices[i+2]];
			pos[7] = vertices[3 * indices[i+2] + 1];
			pos[8] = vertices[3 * indices[i+2] + 2];

			qglviewer::Vec qgl_bar = barycenter(pos);
			centers[i+2] = qgl_bar[1];
		}
		radius.push_back(std::sqrt(s * (s - a) * (s - b) * (s - c)) / s);
	}
}
