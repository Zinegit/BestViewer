#include "include/updateVisibleTriangles.hpp"

std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles)
{
	std::vector<bool> fusion;
	fusion.reserve(front_face_triangles.size());
	for (int i = 0; i < front_face_triangles.size(); i++)
	{
		fusion.push_back(front_face_triangles[i] && inside_frustum_triangles[i]);
	}
	return fusion;
}

std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index_triangles)
{
	std::vector<int> new_index;
	for (int i = 0; i < triangles_to_show.size(); i++)
	{
		if (triangles_to_show[i])
		{
			new_index.push_back(index_triangles[3 * i]);
			new_index.push_back(index_triangles[3 * i + 1]);
			new_index.push_back(index_triangles[3 * i + 2]);
		}
	}
	return new_index;
}

// Might be impossible to modify the vertices because of the indexation
//std::vector<float> updateVertices(std::vector<int>& index_triangles)
//{
//	std::vector<float> new_vertices;
//	for (int i = 0; i < index_triangles.size(); i++)
//	{
//		new_vertices.push_back(3 * index_triangles[i]);
//		new_vertices.push_back(3 * index_triangles[i]+1);
//		new_vertices.push_back(3 * index_triangles[i]+2);
//	}
//}
