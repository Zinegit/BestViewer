#include <vector>
#include <chrono>
#include <QGLViewer/qglviewer.h>
#include "include/isNotOcculted.hpp"

std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
