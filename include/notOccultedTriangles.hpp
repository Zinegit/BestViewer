/**
 * \file notOccultedTriangles.hpp
 * \brief Return a boolean vector representing which triangle is occulted and which is not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <vector>
#include <QGLViewer/qglviewer.h>
#include "include/notOccultedPoints.hpp"

std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
