/**
 * \file frontLine.hpp
 * \brief Return faces of every triangle belonging to the frontline.
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef FRONTLINE_HPP
#define FRONTLINE_HPP

#include <GL/glew.h>

#include <vector>
#include "external/I3S-Meshing/include/halfedgemesh.h"

/**
 * \fn void updateFrontLine(std::list<FaceIter> frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function updates the frontline untill every triangle is predicted. TO DO: This function only works on the monores mesh. The aim of this function will be to calculate
 * \param frontline : The initialized frontline of the object
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param frontline_colors : The triangles that belong to the frontline are associated with one in order to colorize them in blue in addColor
 * \param vertices : Geometrical description of the object
 * \param indices : Topological description of the object
 * \param halfedgeMesh : The instanciation of the halfedgeMesh class
 * \return The distances between each vertex and its prediction
 */
std::vector<float> updateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, std::vector<float>& vertices, std::vector<int>& indices, HalfedgeMesh& halfedgeMesh);

/**
 * \fn void TempUpdateFrontLine(std::list<FaceIter> frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function updates the frontline triangle by triangle, predicts their position and return the distance between the predicted and the real position
 * \param frontline : The initialized frontline of the object
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertices : Geometrical description of the object
 * \param indices : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline are associated with one in order to colorize them in blue in addColor
 * \param halfedgeMesh : The instanciation of the halfedgeMesh class
 * \param true_vertices : The true geometrical description of the triangles to predict
 * \param predicted_vertices : The predicted geometrical description of the triangles to predict
 * \return The distance between the vertex and its prediction
 */
float TempUpdateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<float>& vertices, std::vector<int>& indices, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh, std::vector<float>& true_vertices, std::vector<float>& predicted_vertices);

/**
 * \fn std::vector<FaceIter> getFrontLine(std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function returns a vector of faces that belong to the frontline using the halfedge structure
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param frontline_colors : The triangles that belong to the frontline
 * \param halfedgeMesh : The instanciation of the halfedgeMesh class
 * \return a vector of the faces that belong to the frontline
 */
std::list<FaceIter> getFrontLine(std::vector<int>& triangle_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

/**
 * \fn std::vector<float> predictTriangle(FaceIter& frontline_triangle, HalfedgeIter& frontline_halfedge, HalfedgeMesh& halfedgeMesh)
 * \brief This function returns a vector of faces that belong to the frontline using the halfedge structure
 * \param frontline_halfedge : halfedge of the frontline
 * \return a vector of the faces that belong to the frontline
 */
std::vector<float> predictTriangle(HalfedgeIter& frontline_halfedge);

#endif // FRONTLINE_HPP
