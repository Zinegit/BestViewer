#include "include/backFaceCulling.hpp"

std::vector<float> getNormals(std::vector<float>& vertex_positions, std::vector<int>& index_triangles)
{
	std::vector<float> normals(index_triangles.size(), 0);
	std::vector<float> a(3, 0);
	std::vector<float> b(3, 0);
	Eigen::Vector3d n;
	for (int i = 0; i < index_triangles.size(); i += 3 )
	{
		a[0] = vertex_positions[3 * index_triangles[i+1]] - vertex_positions[3 * index_triangles[i]];
		a[1] = vertex_positions[3 * index_triangles[i+1]+1] - vertex_positions[3 * index_triangles[i]+1];
		a[2] = vertex_positions[3 * index_triangles[i+1]+2] - vertex_positions[3 * index_triangles[i]+2];
		b[0] = vertex_positions[3 * index_triangles[i+2]] - vertex_positions[3 * index_triangles[i]];
		b[1] = vertex_positions[3 * index_triangles[i+2]+1] - vertex_positions[3 * index_triangles[i]+1];
		b[2] = vertex_positions[3 * index_triangles[i+2]+2] - vertex_positions[3 * index_triangles[i]+2];

		Eigen::Vector3d a_e(a[0], a[1], a[2]);
		Eigen::Vector3d b_e(b[0], b[1], b[2]);
		n = a_e.cross(b_e);
		normals[i] = n[0];
		normals[i+1] = n[1];
		normals[i+2] = n[2];
	}
	return normals;
}

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
