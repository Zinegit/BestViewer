#include "include/isInsideFrustum.hpp"

bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
{
	for (int k = 0; k < 6; k += 2)
	{
		if (distanceToPlane(k, pos, plane_coefficients) + distanceToPlane(k+1, pos, plane_coefficients) - plane_coefficients[k][3] - plane_coefficients[k+1][3] > 0.0001)
			return false;
	}
	return true;
}
