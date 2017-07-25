#include "include/isNotOcculted.hpp"

float sign (qglviewer::Vec p1, qglviewer::Vec p2, qglviewer::Vec p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool pointInTriangle (qglviewer::Vec pt, qglviewer::Vec v1, qglviewer::Vec v2, qglviewer::Vec v3)
{
	bool b1, b2, b3;

	b1 = sign(pt, v1, v2) < 0.0f;
	b2 = sign(pt, v2, v3) < 0.0f;
	b3 = sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

bool isNotOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, int point_index, GLdouble plane_coefficients[6][4], std::vector<float>& distances, float& d4)
{
	for (int i = 0; i < index_triangles.size(); i += 3)
	{
		float x1 = vertex_positions[3 * index_triangles[i]];
		float y1 = vertex_positions[3 * index_triangles[i] + 1];
		qglviewer::Vec p1(x1,y1,1);
		float x2 = vertex_positions[3 * index_triangles[i+1]];
		float y2 = vertex_positions[3 * index_triangles[i+1] + 1];
		qglviewer::Vec p2(x2,y2,1);
		float x3 = vertex_positions[3 * index_triangles[i+2]];
		float y3 = vertex_positions[3 * index_triangles[i+2] + 1];
		qglviewer::Vec p3(x3,y3,1);
		float x4 = point[0];
		float y4 = point[1];
		qglviewer::Vec p4(x4,y4,1);
		float d1 = distances[index_triangles[i]];
		float d2 = distances[index_triangles[i+1]];
		float d3 = distances[index_triangles[i+2]];
		if (point_index != index_triangles[i] && point_index != index_triangles[i+1] && point_index != index_triangles[i+2])
		{
			if ((d4 < d1) && (d4 < d2) && (d4 < d3))
			{
				if(pointInTriangle(p4, p1, p2, p3))
				{
					return false;
				}
			}
		}
	}

	return true;
}
