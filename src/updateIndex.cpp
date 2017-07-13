#include "include/updateIndex.hpp"

std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index)
{
	std::vector<int> new_index;
	for (int i = 0; i < triangles_to_show.size(); i++)
	{
		if (triangles_to_show[i])
		{
			new_index.push_back(index[3 * i]);
			new_index.push_back(index[3 * i + 1]);
			new_index.push_back(index[3 * i + 2]);
		}
	}
	return new_index;
}
