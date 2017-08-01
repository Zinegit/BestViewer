/**
 * \file projection.hpp
 * \brief Return the coordinates of the triangles projected on the near plane
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <vector>
#include <QGLViewer/qglviewer.h>

std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane);
