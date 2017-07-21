#include "include/isNotOcculted.hpp"

bool isNotOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, GLdouble plane_coefficients[6][4])
{
	for (int i = 0; i < index_triangles.size(); i += 3)
	{
		float x1 = vertex_positions[3 * index_triangles[i]];
		float y1 = vertex_positions[3 * index_triangles[i] + 1];
		float z1 = vertex_positions_3d[3 * index_triangles[i] + 2];
		float x2 = vertex_positions[3 * index_triangles[i+1]];
		float y2 = vertex_positions[3 * index_triangles[i+1] + 1];
		float z2 = vertex_positions_3d[3 * index_triangles[i+1] + 2];
		float x3 = vertex_positions[3 * index_triangles[i+2]];
		float y3 = vertex_positions[3 * index_triangles[i+2] + 1];
		float z3 = vertex_positions_3d[3 * index_triangles[i+2] + 2];
		float x4 = point[0];
		float y4 = point[1];
		float z4 = point[2];

		float eq1 = x1 * (y2 - y4) + x2 * (y4 - y1) + x4 * (y1 - y2);
		float eq2 = x2 * (y3 - y4) + x3 * (y4 - y2) + x4 * (y2 - y3);
		float eq3 = x3 * (y1 - y4) + x1 * (y4 - y3) + x4 * (y3 - y1);

		qglviewer::Vec point1(x1, y1, z1);
		qglviewer::Vec point2(x2, y2, z2);
		qglviewer::Vec point3(x3, y3, z3);
		qglviewer::Vec point(x4, y4, z4);

		if (point != point1 && point != point2 && point != point3)
		{
			if ((distanceToPlane(3, point, plane_coefficients) < distanceToPlane(3, point1, plane_coefficients)) && (distanceToPlane(3, point, plane_coefficients) < distanceToPlane(3, point2, plane_coefficients)) && (distanceToPlane(3, point, plane_coefficients) < distanceToPlane(3, point3, plane_coefficients)))
			{
				if ((eq1 > 0 && eq2 > 0 && eq3 > 0) || (eq1 < 0 && eq2 < 0 && eq3 < 0))
				{
				return false;
				}
			}
		}
	}

	return true;
}
