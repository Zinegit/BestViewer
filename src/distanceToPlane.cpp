#include "include/distanceToPlane.hpp"

float distanceToPlane(int i, qglviewer::Vec& pos, GLdouble plane_coefficients[6][4])
{
	float distance = (std::abs(plane_coefficients[i][0] * pos[0] + plane_coefficients[i][1] * pos[1] + plane_coefficients[i][2] * pos[2] - plane_coefficients[i][3])) / std::sqrt(std::pow(plane_coefficients[i][0], 2.0) + std::pow(plane_coefficients[i][1], 2.0) + std::pow(plane_coefficients[i][2], 2.0) );
	return distance;
}
