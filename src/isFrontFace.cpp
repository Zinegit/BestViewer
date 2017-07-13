#include "include/isFrontFace.hpp"

std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals)
{
	Eigen::Vector3d cam(direction.x, direction.y, direction.z);
	std::vector<bool> front_face_triangles(normals.size()/3, 0);
	int j = 0;
	for (int i = 0; i < normals.size(); i += 3)
	{
		Eigen::Vector3d normal(normals[i], normals[i + 1], normals[i + 2]);
		front_face_triangles[j] = normal.dot(cam) <= 0;
		j += 1;
	}
	return front_face_triangles;
}
