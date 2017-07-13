#include "include/areInsideFrustum.hpp"

#include <QGLViewer/qglviewer.h>

std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4] )
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
