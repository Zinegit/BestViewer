#include "include/incircle.hpp"

void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius)
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
		centers [i+2] = (a * vertex_positions[3 * index_triangles[i] + 2] + b * vertex_positions[3 * index_triangles[i+1] + 2] + c * vertex_positions[3 * index_triangles[i+2] + 2]) / p ;

		radius.push_back(std::sqrt(s * (s - a) * (s - b) * (s - c)) / s);
	}
}
