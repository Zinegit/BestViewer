/**
 * \file updateVisibleTriangles.hpp
 * \brief These functions are used to udpate the triangles to show according to the differents cullings that have been used
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef UPDATEINVISIBLETRIANGLES_HPP
#define UPDATEINVISIBLETRIANGLES_HPP

#include <vector>

/**
 * \fn std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles)
 * \brief This function returns a vector that verifies that each triangle is both frontface and inside the frustum
 * \param front_face_triangles : Triangles that are oriented towards the viewer
 * \param inside_frustum_triangles : Triangles that are inside the frustum
 * \return A vector of booleans representing triangles that are both frontface and inside the frustum
 */
std::vector<bool> fusionBools(std::vector<bool>& front_face_triangles, std::vector<bool>& inside_frustum_triangles);

/**
 * \fn std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index)
 * \brief This function updates the index_triangles vector in order to select only the ones that are supposed to be drawn
 * \param triangles_to_show : Vector of booleans describing which triangle is supposed to be drawn
 * \param index_triangles : Topological description of the object
 * \return New index_triangles containing only the triangles to draw
 */
std::vector<int> updateIndex(std::vector<bool>& triangles_to_show, std::vector<int>& index_triangles);

std::vector<float> updateVertices(std::vector<int>& index_triangles);

#endif // UPDATEINVISIBLETRIANGLES_HPP
