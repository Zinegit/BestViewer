/**
 * \file depthCulling.hpp
 * \brief Contains all the functions used for depth culling process. The algorithm is to heavy to run so it is not used here
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef DEPTHCULLING_HPP
#define DEPTHCULLING_HPP

#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/Dense>

/**
 * \fn float sign (qglviewer::Vec p1, qglviewer::Vec p2, qglviewer::Vec p3)
 * \brief This function returns the result of the equation checking if p1 is at the left or at the right of the line passing through p2 and p3.
 * \param p1 : the point considered
 * \param p2 : one of the vertices of the triangle
 * \param p3 : one of the vertices of the triangle
 * \return Result of the equation (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y)
 */
float sign (qglviewer::Vec p1, qglviewer::Vec p2, qglviewer::Vec p3);

/**
 * \fn bool pointInTriangle (qglviewer::Vec pt, qglviewer::Vec v1, qglviewer::Vec v2, qglviewer::Vec v3)
 * \brief This function returns true if the point is inside the triangle and false if it is. If the point pt is at the right of each of the three lines forming the triangle then the point is inside the triangle
 * \param pt : The point whose presence in the triangle is considered
 * \param v1 : The first point of the triangle
 * \param v2 : The seconde point of the triangle
 * \param v3 : The third point of the triangle
 * \return True if the point is outside the triangle and false if it is inside
 */
bool pointInTriangle (qglviewer::Vec pt, qglviewer::Vec v1, qglviewer::Vec v2, qglviewer::Vec v3);

/**
 * \fn bool isNotOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, int point_index, GLdouble plane_coefficients[6][4], std::vector<float>& distances, float& d4)
 * \brief This function returns true if the input point is not occulted and false if it is
 * \param vertices : Geometrical description of the object projected in the near_plane
 * \param indices : Topological description of the object
 * \param point : A vertex
 * \param point_index : The index of the point in vertex_positions
 * \param distances : The distances of every vertex from the near plane
 * \param d4 : The distance of the point from the near plane
 * \return True if the point is not occulted and false if it is
 */
bool isNotOcculted(std::vector<float>& vertices, std::vector<int>& indices, std::vector<float>& point, int point_index, std::vector<float>& distances, float& d4);

/**
 * \fn std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances)
 * \brief This function returns a vector of booleans. True is for a point visible and false for an occulted point. This function is to heavy to run so it is not used here.
 * \param vertices : Geometrical description of the object projected in the near_plane
 * \param vertices_3d : Geometrical description of the object
 * \param indices : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \param distances : The distances of every vertex from the near plane
 * \return Vector of booleans describing which point is occulted and which is not
 */
std::vector<bool> notOccultedPoints(std::vector<float>& vertices, std::vector<float>& vertices_3d, std::vector<int>& indices, GLdouble plane_coefficients[6][4], std::vector<float>& distances);

/**
 * \fn std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4])
 * \brief This function returns a vector of booleans. True is for a triangle visible and false for an occulted triangle. This function is to heavy to run so it is not used here.
 * \param vertices : Geometrical description of the object projected in the near_plane
 * \param vertices_3d : Geometrical description of the object
 * \param indices : Topological description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \return Vector of booleans describing which triangle is occulted and which is not
 */
std::vector<bool> notOccultedTriangles(std::vector<float>& vertices, std::vector<float>& vertices_3d, std::vector<int>& indices, GLdouble plane_coefficients[6][4]);

#endif // DEPTHCULLING_HPP
