/**
 * \file isInsideFrustum.hpp
 * \brief Return a boolean representing whether a triangle is inside the frustum or not
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <QGLViewer/qglviewer.h>
#include "include/distanceToPlane.hpp"

bool isInsideFrustum(qglviewer::Vec& pos, GLdouble plane_coefficients[6][4]);
