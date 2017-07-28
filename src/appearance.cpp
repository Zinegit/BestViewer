#include "include/appearance.hpp"
#include <iostream>

std::vector<float> appearance(std::vector<bool> triangles_to_show_t1, std::vector<bool> triangles_to_show_t2)
{
	std::vector<float> appearing_triangles;
	appearing_triangles.reserve(triangles_to_show_t1.size());
	for (int i = 0; i < triangles_to_show_t1.size(); i++)
	{
		if (triangles_to_show_t1[i] == 0 and triangles_to_show_t2[i] == 1)
		{
			appearing_triangles.push_back(1);
		}
		else if (triangles_to_show_t1[i] == 1 and triangles_to_show_t2[i] == 0)
		{
			appearing_triangles.push_back(2);
		}
		else if (triangles_to_show_t1[i] == 0 and triangles_to_show_t2[i] == 0)
		{
			appearing_triangles.push_back(0);
		}
		else if (triangles_to_show_t1[i] == 1 and triangles_to_show_t2[i] == 1)
		{
			appearing_triangles.push_back(0);
		}
	}
	return appearing_triangles;
}
