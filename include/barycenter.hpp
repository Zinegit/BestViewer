/**
 * \file barycenter.hpp
 * \brief Return the barycenter of an object
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef BARYCENTER_HPP
#define BARYCENTER_HPP

#include <vector>
#include <QGLViewer/qglviewer.h>

/**
 * \fn const qglviewer::Vec barycenter(std::vector<float>& vertices)
 * \brief This function returns the barycenter of the object
 * \param vertices : Geometrical description of the object
 * \return The barycenter of the object
 */
const qglviewer::Vec barycenter(std::vector<float>& vertices);

#endif // BARYCENTER_HPP
