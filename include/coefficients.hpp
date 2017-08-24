/**
 * \file coefficients.hpp
 * \brief generates all the the coefficient files used by every client connected to the server. These files contain the prediction errors of every triangle
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include "include/frontLine.hpp"
#include "include/toTxt.hpp"
#include "external/I3S-Meshing/include/halfedgemesh.h"

/**
 * \fn findCoefficients(std::vector<float>& vertex_positions, std::vector<int> &index_triangles, std::vector<int> &triangles_status, HalfedgeMesh& halfedgeMesh, int depth)
 * \brief This function generates all the the coefficient files used by every client connected to the server. These files contain the prediction errors of every triangle
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param triangle_status : State of every triangle (appeared/disappeared/same state)
 * \param halfedgeMesh : The instanciation of the halfedgeMesh class
 * \param depth : The resolution wanted
 * \return The distance of a vertex from one of the frustum's planes
 */
void findCoefficients(std::vector<float>& vertex_positions, std::vector<int> &index_triangles, std::vector<int> &triangles_status, HalfedgeMesh& halfedgeMesh, int depth);

#endif // COEFFICIENTS_H
