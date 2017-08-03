/**
 * \file isFrontFace.cpp
 * \brief Return a boolean vector representing which triangle is front face and which is not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/isFrontFace.hpp"

/**
 * \fn std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals)
 * \brief This function checks for every triangle whether it is frontface or not. A dot product is made between the viewer's line-of-sight and the each triangle's normal.
 *
 * \param direction : the viewer's line-of-sight
 * \param normals : the normal of each triangle
 * \return Vector of booleans describing which triangle is frontface and which is not
 */
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
