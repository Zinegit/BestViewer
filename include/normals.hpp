/**
 * \file normals.hpp
 * \brief Calculate normals of every triangle
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <vector>
#include <Eigen/Dense>

// Return the normal of the input triangle

std::vector<float> getNormals(std::vector<float>& vertex_positions, std::vector<int>& index_triangles);
