#include <vector>
#include "include/isInsideFrustum.hpp"

std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
