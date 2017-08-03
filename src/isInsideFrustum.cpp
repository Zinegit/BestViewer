/**
 * \file isInsideFrustum.cpp
 * \brief Return a boolean representing whether a triangle is inside the frustum or not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/isInsideFrustum.hpp"

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
