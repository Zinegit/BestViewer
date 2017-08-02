#include "include/addColor.hpp"

std::vector<float> colorize(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors)
{
	std::vector<float> colors(vertex_positions.size(), 1.0);
	for(int i = 0; i < triangles_status.size(); i++)
	{
		// If triangle's state does not change, color is white
		if (triangles_status[i] == 0)
		{
			colors[3 * index_triangles[3 * i]] = 1.0;
			colors[3 * index_triangles[3 * i] + 1] = 1.0;
			colors[3 * index_triangles[3 * i] + 2] = 1.0;

			colors[3 * index_triangles[3 * i + 1]] = 1.0;
			colors[3 * index_triangles[3 * i + 1] + 1] = 1.0;
			colors[3 * index_triangles[3 * i + 1] + 2] = 1.0;

			colors[3 * index_triangles[3 * i + 2]] = 1.0;
			colors[3 * index_triangles[3 * i + 2] + 1] = 1.0;
			colors[3 * index_triangles[3 * i + 2] + 2] = 1.0;
		}
		// If triangle appears, color is green
		else if (triangles_status[i] == 1)
		{
			colors[3 * index_triangles[3 * i]] = 0;
			colors[3 * index_triangles[3 * i] + 1] = 1.0;
			colors[3 * index_triangles[3 * i] + 2] = 0;

			colors[3 * index_triangles[3 * i + 1]] = 0;
			colors[3 * index_triangles[3 * i + 1] + 1] = 1.0;
			colors[3 * index_triangles[3 * i + 1] + 2] = 0;

			colors[3 * index_triangles[3 * i + 2]] = 0;
			colors[3 * index_triangles[3 * i + 2] + 1] = 1.0;
			colors[3 * index_triangles[3 * i + 2] + 2] = 0;
		}
		// If triangle disappears, color is red
		else if (triangles_status[i] == 2)
		{
			colors[3 * index_triangles[3 * i]] = 1.0;
			colors[3 * index_triangles[3 * i] + 1] = 0;
			colors[3 * index_triangles[3 * i] + 2] = 0;

			colors[3 * index_triangles[3 * i + 1]] = 1.0;
			colors[3 * index_triangles[3 * i + 1] + 1] = 0;
			colors[3 * index_triangles[3 * i + 1] + 2] = 0;

			colors[3 * index_triangles[3 * i + 2]] = 1.0;
			colors[3 * index_triangles[3 * i + 2] + 1] = 0;
			colors[3 * index_triangles[3 * i + 2] + 2] = 0;
		}
		if (frontline_colors[i] == 1)
		{
			std::cout << "blue" << std::endl;
			colors[3 * index_triangles[3 * i]] = 0;
			colors[3 * index_triangles[3 * i] + 1] = 0;
			colors[3 * index_triangles[3 * i] + 2] = 1.0;

			colors[3 * index_triangles[3 * i + 1]] = 0;
			colors[3 * index_triangles[3 * i + 1] + 1] = 0;
			colors[3 * index_triangles[3 * i + 1] + 2] = 1.0;

			colors[3 * index_triangles[3 * i + 2]] = 0;
			colors[3 * index_triangles[3 * i + 2] + 1] = 0;
			colors[3 * index_triangles[3 * i + 2] + 2] = 1.0;
		}
	}
	return colors;
}
