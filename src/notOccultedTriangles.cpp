#include "include/notOccultedTriangles.hpp"

std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
{

	std::vector<bool> not_occulted_triangles;
	std::vector<bool> not_occulted_points = notOccultedPoints(vertex_positions, vertex_positions_3d, index_triangles, plane_coefficients);
	for (int i = 0; i < index_triangles.size(); i += 3)
	{
		not_occulted_triangles.push_back(not_occulted_points[index_triangles[i]] || not_occulted_points[index_triangles[i+1]] || not_occulted_points[index_triangles[i+2]]);
	}
	return not_occulted_triangles;
}
