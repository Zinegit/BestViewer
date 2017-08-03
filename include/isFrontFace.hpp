#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/Dense>

std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals);
