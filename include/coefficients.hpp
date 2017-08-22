#ifndef COEFFICIENTS_H
#define COEFFICIENTS_H

#include <vector>
#include <algorithm>
#include <stdio.h>
#include "include/frontLine.hpp"
#include "include/toTxt.hpp"
#include "external/I3S-Meshing/include/halfedgemesh.h"

void findCoefficients(std::vector<float>& vertex_positions, std::vector<int> &index_triangles, std::vector<int> &triangles_status, HalfedgeMesh& halfedgeMesh, int depth);

#endif // COEFFICIENTS_H
