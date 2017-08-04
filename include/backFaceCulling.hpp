#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/Dense>

// Return the normals of the triangles
std::vector<float> getNormals(std::vector<float>& vertex_positions, std::vector<int>& index_triangles);

std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals);
