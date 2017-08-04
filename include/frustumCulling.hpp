#include <vector>
#include <QGLViewer/qglviewer.h>

float distanceToPlane(int i, qglviewer::Vec& pos, GLdouble plane_coefficients[6][4]);

bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4]);

std::vector<bool> areInsideFrustum(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, GLdouble plane_coefficients[6][4]);
