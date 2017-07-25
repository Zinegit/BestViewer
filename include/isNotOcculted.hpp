#include <vector>
#include <iostream>
#include <chrono>
#include <QGLViewer/qglviewer.h>
#include "include/distanceToPlane.hpp"

#include <Eigen/Dense>

bool isNotOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, int point_index, GLdouble plane_coefficients[6][4], std::vector<float>& distances, float& d4);
