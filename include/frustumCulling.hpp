/**
 * \file frustumCulling.hpp
 * \brief Contains all the functions used for frustum culling process
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef FRUSTUMCULLING_HPP
#define FRUSTUMCULLING_HPP

#include <vector>
#include <cmath>
#include <QGLViewer/qglviewer.h>

/**
 * \fn float distanceToPlane(int i, qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
 * \brief This function calculates the distance of a vertex from one of the frustum's planes
 * \param i : 0 -> 5 describes which plane of the frustum is used
 * \param pos : A vertex
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return The distance of a vertex from one of the frustum's planes
 */
float distanceToPlane(int i, qglviewer::Vec& pos, GLdouble plane_coefficients[6][4]);

/**
 * \fn bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
 * \brief This function checks for a vertex whether it is in the frustum or not
 * \param pos : A vertex
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return A boolean being true if the point is in the frustum and false if it is not
 */
bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4]);

/**
 * \fn std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
 * \brief This function checks for every triangle whether it is in the frustum or not. If at least one of the vertices of a triangle is in the frustum then the triangle is considered in the frustum. For each triangle this function calls isInsideFrustum in order to check if one of its vertices is inside the frustum
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return Vector of booleans describing which triangle is inside the frustum and which is not
 */
std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);

#endif // FRUSTUMCULLING_HPP
