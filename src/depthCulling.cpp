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

bool isNotOcculted(std::vector<float>& vertices, std::vector<int>& indices, std::vector<float>& point, int point_index, std::vector<float>& distances, float& d4)
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		float x1 = vertices[3 * indices[i]];
		float y1 = vertices[3 * indices[i] + 1];
		qglviewer::Vec p1(x1,y1,1);
		float x2 = vertices[3 * indices[i+1]];
		float y2 = vertices[3 * indices[i+1] + 1];
		qglviewer::Vec p2(x2,y2,1);
		float x3 = vertices[3 * indices[i+2]];
		float y3 = vertices[3 * indices[i+2] + 1];
		qglviewer::Vec p3(x3,y3,1);
		float x4 = point[0];
		float y4 = point[1];
		qglviewer::Vec p4(x4,y4,1);
		float d1 = distances[indices[i]];
		float d2 = distances[indices[i+1]];
		float d3 = distances[indices[i+2]];
		if (point_index != indices[i] && point_index != indices[i+1] && point_index != indices[i+2])
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

std::vector<bool> notOccultedPoints(std::vector<float>& vertices, std::vector<float>& vertices_3d, std::vector<int>& indices, GLdouble plane_coefficients[6][4], std::vector<float>& distances)
{
	std::vector<bool> not_occulted_points;
	not_occulted_points.reserve(vertices.size() / 3);
	int j = 0;
	for (int i = 0; i < vertices.size(); i += 3)
	{
		std::vector<float> point;
		point.push_back(vertices[i]);
		point.push_back(vertices[i+1]);
		point.push_back(vertices_3d[i+2]);
		float d4 = distances[j];
		not_occulted_points.push_back(isNotOcculted(vertices, indices, point, j, distances, d4));
		j += 1;
	}
	return not_occulted_points;
}

std::vector<bool> notOccultedTriangles(std::vector<float>& vertices, std::vector<float>& vertices_3d, std::vector<int>& indices, GLdouble plane_coefficients[6][4])
{
	std::vector<float> distances;
	distances.reserve(vertices.size() / 3);
	for (int i = 0; i < vertices.size(); i += 3)
	{
		float x = vertices[i];
		float y = vertices[i + 1];
		float z = vertices_3d[i + 2];
		qglviewer::Vec point1(x, y, z);
		distances.push_back(distanceToPlane(3, point1, plane_coefficients));
	}
	std::vector<bool> not_occulted_triangles;
	not_occulted_triangles.reserve(indices.size() / 3);
	std::vector<bool> not_occulted_points = notOccultedPoints(vertices, vertices_3d, indices, plane_coefficients, distances);
	for (int i = 0; i < indices.size(); i += 3)
	{
		not_occulted_triangles.push_back(not_occulted_points[indices[i]] || not_occulted_points[indices[i+1]] || not_occulted_points[indices[i+2]]);
	}
	return not_occulted_triangles;
}
