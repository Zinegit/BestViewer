/**
 * \file notOccultedPoints.hpp
 * \brief Return a boolean vector representing which point is occulted and which is not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <vector>
#include <chrono>
#include <QGLViewer/qglviewer.h>
#include "include/isNotOcculted.hpp"

std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances);
