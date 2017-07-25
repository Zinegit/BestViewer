#include "include/fusionBools.hpp"

std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles)
{
	std::vector<bool> fusion;
	for (int i = 0; i < front_face_triangles.size(); i++)
	{
		fusion.push_back(front_face_triangles[i] && inside_frustum_triangles[i]);
	}
	return fusion;
}


