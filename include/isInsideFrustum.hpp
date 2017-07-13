#include <QGLViewer/qglviewer.h>
#include "include/distanceToPlane.hpp"

bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4]);
