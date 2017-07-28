#include "include/addColor.hpp"

std::vector<float> colorize(std::vector<float> appearing_triangles, std::vector<float> vertex_positions, std::vector<int> index_triangles)
{
	std::vector<float> colors(vertex_positions.size(), 1.0);
	for(int i = 0; i < appearing_triangles.size(); i++)
	{
		// If triangle's state does not change, color is white
		if (appearing_triangles[i] == 0)
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
		else if (appearing_triangles[i] == 1)
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
		else if (appearing_triangles[i] == 2)
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
	}
	return colors;
}
