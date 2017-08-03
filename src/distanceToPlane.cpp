/**
 * \file distanceToPlane.cpp
 * \brief Return the distance of a vertex to the near/far plane
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/distanceToPlane.hpp"

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
