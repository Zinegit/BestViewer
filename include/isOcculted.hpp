#include <vector>
#include <iostream>
#include <QGLViewer/qglviewer.h>
#include "include/distanceToPlane.hpp"

bool isOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, GLdouble plane_coefficients[6][4]);
