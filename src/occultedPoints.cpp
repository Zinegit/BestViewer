#include "include/occultedPoints.hpp"

std::vector<bool> occultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
{
	std::vector<bool> occulted_points;
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		std::vector<float> point;
		point.push_back(vertex_positions[9]);
		point.push_back(vertex_positions[10]);
		point.push_back(vertex_positions_3d[11]);
		occulted_points.push_back(isOcculted(vertex_positions, vertex_positions_3d, index_triangles, point, plane_coefficients));
	}
	return occulted_points;
}
