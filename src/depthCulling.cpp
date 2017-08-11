#include "include/depthCulling.hpp"
#include "include/frustumCulling.hpp"

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

std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances)
{
	std::vector<bool> not_occulted_points;
	not_occulted_points.reserve(vertex_positions.size() / 3);
	int j = 0;
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		std::vector<float> point;
		point.push_back(vertex_positions[i]);
		point.push_back(vertex_positions[i+1]);
		point.push_back(vertex_positions_3d[i+2]);
		float d4 = distances[j];
		not_occulted_points.push_back(isNotOcculted(vertex_positions, vertex_positions_3d, index_triangles, point, j, plane_coefficients, distances, d4));
		j += 1;
	}
	return not_occulted_points;
}

std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
{
	std::vector<float> distances;
	distances.reserve(vertex_positions.size() / 3);
	for (int i = 0; i < vertex_positions.size(); i += 3)
	{
		float x = vertex_positions[i];
		float y = vertex_positions[i + 1];
		float z = vertex_positions_3d[i + 2];
		qglviewer::Vec point1(x, y, z);
		distances.push_back(distanceToPlane(3, point1, plane_coefficients));
	}
	std::vector<bool> not_occulted_triangles;
	not_occulted_triangles.reserve(index_triangles.size() / 3);
	std::vector<bool> not_occulted_points = notOccultedPoints(vertex_positions, vertex_positions_3d, index_triangles, plane_coefficients, distances);
	for (int i = 0; i < index_triangles.size(); i += 3)
	{
		not_occulted_triangles.push_back(not_occulted_points[index_triangles[i]] || not_occulted_points[index_triangles[i+1]] || not_occulted_points[index_triangles[i+2]]);
	}
	return not_occulted_triangles;
}
