/**
 * \file frustumCulling.cpp
 * \brief Contains all the functions used for frustum culling process
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/frustumCulling.hpp"

#include <QGLViewer/qglviewer.h>

/**
 * \fn float distanceToPlane(int i, qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
 * \brief This function calculates the distance of a vertex from one of the frustum's planes
 *
 * \param i : 0 -> 5 describes which plane of the frustum is used
 * \param pos : A vertex
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return The distance of a vertex from one of the frustum's planes
 */
float distanceToPlane(int i, qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
{
	float distance = (std::abs(plane_coefficients[i][0] * pos[0] + plane_coefficients[i][1] * pos[1] + plane_coefficients[i][2] * pos[2] - plane_coefficients[i][3])) / std::sqrt(std::pow(plane_coefficients[i][0], 2.0) + std::pow(plane_coefficients[i][1], 2.0) + std::pow(plane_coefficients[i][2], 2.0) );
	return distance;
}

/**
 * \fn bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
 * \brief This function checks for a vertex whether it is in the frustum or not
 *
 * \param pos : A vertex
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 *
 * \return A boolean being true if the point is in the frustum and false if it is not
 */
bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
{
	for (int k = 0; k < 6; k += 2)
	{
		if (distanceToPlane(k, pos, plane_coefficients) + distanceToPlane(k+1, pos, plane_coefficients) - plane_coefficients[k][3] - plane_coefficients[k+1][3] > 0.0001)
			return false;
	}
	return true;
}


/**
 * \fn std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
 * \brief This function checks for every triangle whether it is in the frustum or not. If at least one of the vertices of a triangle is in the frustum then the triangle is considered in the frustum. For each triangle this function calls isInsideFrustum in order to check if one of its vertices is inside the frustum
 *
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return Vector of booleans describing which triangle is inside the frustum and which is not
 */
std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
{
	// Create a boolean table returning true for each point inside the frustum and false for each point that is not
	std::vector<bool> inside_frustum_points;
	qglviewer::Vec pos;
	std::vector<bool> inside_frustum_triangles;
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		pos[0] = vertex_positions[i];
		pos[1] = vertex_positions[i+1];
		pos[2] = vertex_positions[i+2];
		inside_frustum_points.push_back(isInsideFrustum(pos, plane_coefficients));
	}
	for (int j = 0; j < index_triangles.size(); j += 3)
	{
		inside_frustum_triangles.push_back(inside_frustum_points[index_triangles[j]] || inside_frustum_points[index_triangles[j+1]] || inside_frustum_points[index_triangles[j+2]]);
	}
	return inside_frustum_triangles;
}
