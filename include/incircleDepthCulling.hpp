#include <vector>
#include <QGLViewer/qglviewer.h>
#include "include/barycenter.hpp"
#include <iostream>

std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane);

void incircle (std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<float>& centers, std::vector<float>& radius, bool far_plane);
