/**
 * \file backFaceCulling.hpp
 * \brief Contains all the functions used for backface culling process
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef BACKFACECULLING_HPP
#define BACKFACECULLING_HPP

#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/Dense>

/**
 * \fn std::vector<float> getNormals(std::vector<float>& vertex_positions, std::vector<int>& index_triangles)
 * \brief This function calculates the normal of every triangle using the cross product of two vertices.
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \return The normal of each triangle
 */
std::vector<float> getNormals(std::vector<float>& vertex_positions, std::vector<int>& index_triangles);

/**
 * \fn std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals)
 * \brief This function checks for every triangle whether it is frontface or not. A dot product is made between the viewer's line-of-sight and the each triangle's normal.
 * \param direction : the viewer's line-of-sight
 * \param normals : the normal of each triangle
 * \return Vector of booleans describing which triangle is frontface and which is not
 */
std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals);

#endif // BACKFACECULLING_HPP
