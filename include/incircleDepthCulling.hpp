/**
 * \file incircleDepthCulling.hpp
 * \brief These functions could be used to implement a depth culling based on the incircle of each triangle instead of the whole triangle to make it faster. Not tested...
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef INCIRCLEDEPTHCULLING_HPP
#define INCIRCLEDEPTHCULLING_HPP

#include <vector>
#include <iostream>
#include <cmath>

#include <QGLViewer/qglviewer.h>
#include "include/barycenter.hpp"

/**
 * \fn std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane)
 * \brief This function projects every vertex in the near/far plane
 * \param vertex_positions : Geometrical description of the object
 * \param plane_coefficients[6][4] : List of lists containing the frustum's planes' coefficients
 * \param nb_plane : 0 -> 5 describes which plane of the frustum is used (3 or 4 should be used because they represent the near and far planes)
 * \return vertex_positions with the z coordinate of every vertex being the z coordinate of the near/far plane
 */
std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane);

/**
 * \fn void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius, bool far_plane)
 * \brief This function returns the incircle of each triangle. This function is not currently used by could be in order to simplify the depth culling that is currently to slow to be used.
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param centers : The center of each incircle
 * \param radius : The radius of each incircle
 * \param far_plane : if true, the z coordinate of the center is the same as the far plane's. If not, the z coordiante is the one of the barycenter of the triangle.
 * \return nothing but fills the vectors describing each incircle
 */
void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius, bool far_plane);

#endif // INCIRCLEDEPTHCULLING_HPP
