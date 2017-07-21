#include "include/notOccultedPoints.hpp"

std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
{
	std::vector<bool> not_occulted_points;
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		std::vector<float> point;
		point.push_back(vertex_positions[i]);
		point.push_back(vertex_positions[i+1]);
		point.push_back(vertex_positions_3d[i+2]);
		not_occulted_points.push_back(isNotOcculted(vertex_positions, vertex_positions_3d, index_triangles, point, plane_coefficients));
	}
	return not_occulted_points;
}
