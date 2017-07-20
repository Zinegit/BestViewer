#include <vector>
#include <QGLViewer/qglviewer.h>
#include "include/isOcculted.hpp"

std::vector<bool> occultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
