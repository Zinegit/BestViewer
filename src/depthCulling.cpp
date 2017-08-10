/**
 * \file depthCulling.cpp
 * \brief Contains all the functions used for depth culling process. The algorithm is to heavy to run so it is not used here
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/depthCulling.hpp"
#include "include/frustumCulling.hpp"

/**
 * \fn float sign (qglviewer::Vec p1, qglviewer::Vec p2, qglviewer::Vec p3)
 * \brief This function returns the result of the equation checking if p1 is at the left or at the right of the line passing through p2 and p3.
 * \param p1 : the point considered
 * \param p2 : one of the vertices of the triangle
 * \param p3 : one of the vertices of the triangle
 * \return Result of the equation (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)
 */
float sign (qglviewer::Vec p1, qglviewer::Vec p2, qglviewer::Vec p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

/**
 * \fn bool pointInTriangle (qglviewer::Vec pt, qglviewer::Vec v1, qglviewer::Vec v2, qglviewer::Vec v3)
 * \brief This function returns true if the point is inside the triangle and false if it is. If the point pt is at the right of each of the three lines forming the triangle then the point is inside the triangle
 * \param pt : The point whose presence in the triangle is considered
 * \param v1 : The first point of the triangle
 * \param v2 : The seconde point of the triangle
 * \param v3 : The third point of the triangle
 * \return True if the point is outside the triangle and false if it is inside
 */
bool pointInTriangle (qglviewer::Vec pt, qglviewer::Vec v1, qglviewer::Vec v2, qglviewer::Vec v3)
{
	bool b1, b2, b3;

	b1 = sign(pt, v1, v2) < 0.0f;
	b2 = sign(pt, v2, v3) < 0.0f;
	b3 = sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
}

/**
 * \fn bool isNotOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, int point_index, GLdouble plane_coefficients[6][4], std::vector<float>& distances, float& d4)
 * \brief This function returns true if the input point is not occulted and false if it is
 * \param vertex_positions : Geometrical description of the object projected in the near_plane
 * \param vertex_positions_3d : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param point : A vertex
 * \param point_index : The index of the point in vertex_positions
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \param distances : The distances of every vertex from the near plane
 * \param d4 : The distance of the point from the near plane
 * \return True if the point is not occulted and false if it is
 */
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

/**
 * \fn std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances)
 * \brief This function returns a vector of booleans. True is for a point visible and false for an occulted point. This function is to heavy to run so it is not used here.
 * \param vertex_positions : Geometrical description of the object projected in the near_plane
 * \param vertex_positions_3d : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \param distances : The distances of every vertex from the near plane
 * \return Vector of booleans describing which point is occulted and which is not
 */
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

/**
 * \fn std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
 * \brief This function returns a vector of booleans. True is for a triangle visible and false for an occulted triangle. This function is to heavy to run so it is not used here.
 * \param vertex_positions : Geometrical description of the object projected in the near_plane
 * \param vertex_positions_3d : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return Vector of booleans describing which triangle is occulted and which is not
 */
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
