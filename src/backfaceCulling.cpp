#include "include/backFaceCulling.hpp"

std::vector<float> getNormals(std::vector<float>& vertices, std::vector<int>& indices)
{
	std::vector<float> normals(indices.size(), 0);
	std::vector<float> a(3, 0);
	std::vector<float> b(3, 0);
	Eigen::Vector3d n;
	for (int i = 0; i < indices.size(); i += 3 )
	{
		a[0] = vertices[3 * indices[i+1]] - vertices[3 * indices[i]];
		a[1] = vertices[3 * indices[i+1]+1] - vertices[3 * indices[i]+1];
		a[2] = vertices[3 * indices[i+1]+2] - vertices[3 * indices[i]+2];
		b[0] = vertices[3 * indices[i+2]] - vertices[3 * indices[i]];
		b[1] = vertices[3 * indices[i+2]+1] - vertices[3 * indices[i]+1];
		b[2] = vertices[3 * indices[i+2]+2] - vertices[3 * indices[i]+2];

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
