/**
 * \file isFrontFace.hpp
 * \brief Return a boolean vector representing which triangle is front face and which is not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/Dense>

std::vector<bool> isFrontFace(qglviewer::Vec& direction, std::vector<float>& normals);
