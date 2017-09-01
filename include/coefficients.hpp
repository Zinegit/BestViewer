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
 * \fn void findCoefficients(std::vector<float>& vertices, std::vector<int>& indices, HalfedgeMesh& old_halfedgeMesh, HalfedgeMesh& halfedgeMesh, int depth);
 * \brief This function generates all the the coefficient files used by every client connected to the server. These files contain the prediction errors of every triangle
 * \param vertices : Geometrical description of the object
 * \param indices : Topological description of the object
 * \param old_halfedgeMesh : The coarse halfedgeMesh
 * \param halfedgeMesh : The instanciation of the halfedgeMesh class
 * \param depth : The resolution wanted
 * \return void
 */
void findCoefficients(std::vector<float>& vertices, std::vector<int>& indices, HalfedgeMesh& old_halfedgeMesh, HalfedgeMesh& halfedgeMesh, int depth);

#endif // COEFFICIENTS_H
