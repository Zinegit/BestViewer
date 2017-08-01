/**
 * \file incircle.hpp
 * \brief Return incircle of every triangle
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <vector>
#include <QGLViewer/qglviewer.h>
#include "include/barycenter.hpp"
#include <iostream>

void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius, bool far_plane);
