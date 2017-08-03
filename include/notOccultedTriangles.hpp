#include <vector>
#include <QGLViewer/qglviewer.h>
#include "include/notOccultedPoints.hpp"

std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
