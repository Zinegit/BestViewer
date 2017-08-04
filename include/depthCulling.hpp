#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/Dense>

float sign (qglviewer::Vec p1, qglviewer::Vec p2, qglviewer::Vec p3);

bool pointInTriangle (qglviewer::Vec pt, qglviewer::Vec v1, qglviewer::Vec v2, qglviewer::Vec v3);

bool isNotOcculted(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, std::vector<float>& point, int point_index, GLdouble plane_coefficients[6][4], std::vector<float>& distances, float& d4);

std::vector<bool> notOccultedPoints(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4], std::vector<float>& distances);

std::vector<bool> notOccultedTriangles(std::vector<float>& vertex_positions, std::vector<float>& vertex_positions_3d, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
