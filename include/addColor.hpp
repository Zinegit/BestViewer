/**
 * \file addColor.hpp
 * \brief This function returns a vector of color to visualize which triangle appears, disappears, stays in the same state or belongs to frontline.
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef ADDCOLOR_HPP
#define ADDCOLOR_HPP

#include <vector>
#include <iostream>

/**
 * \fn std::vector<float> colorize(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors)
 * \brief Function used to create the vector filled with the color of each vertex that is to be displayed in the viewer
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline
 * \return Vector filled with the color of each vertex of the object.
 */
std::vector<float> colorize(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors);

#endif // ADDCOLOR_HPP
