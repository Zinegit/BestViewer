#include <iostream>
#include "include/appearance.hpp"

std::vector<int> appearance(std::vector<bool>& triangles_to_show_t1, std::vector<bool>& triangles_to_show_t2)
{
	std::vector<int> appearing_triangles;
	appearing_triangles.reserve(triangles_to_show_t1.size());
	for (int i = 0; i < triangles_to_show_t1.size(); i++)
	{
		if (triangles_to_show_t1[i] == 0 && triangles_to_show_t2[i] == 1)
		{
			appearing_triangles.push_back(1);
		}
		else if (triangles_to_show_t1[i] == 1 && triangles_to_show_t2[i] == 0)
		{
			appearing_triangles.push_back(2);
		}
		else if (triangles_to_show_t1[i] == triangles_to_show_t2[i])
		{
			appearing_triangles.push_back(0);
		}
	}
	return appearing_triangles;
}
