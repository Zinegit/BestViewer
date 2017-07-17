#include <vector>
#include <QGLViewer/qglviewer.h>

std::vector<float> project(std::vector<float>& vertex_positions, GLdouble plane_coefficients[6][4], int nb_plane);
