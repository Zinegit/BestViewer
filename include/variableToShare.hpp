/**
 * \file variableToShare.hpp
 * \brief The structure containing every variable shared between viewer and observer
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef VARIABLETOSHARE_H
#define VARIABLETOSHARE_H

#include "halfedgemesh.h"

/**
 * \struct variable_to_share
 * \brief Set of variable shared by the viewer and the observer
 */
typedef struct variable_to_share
{
	std::vector<float> vertex_positions;
	std::vector<int> index;
	std::vector <float> colors;
	std::vector <float> texture;
	GLuint vertex_buffer;
	GLuint index_buffer;
	GLuint color_buffer;
	GLuint texture_buffer;
	float* pointer_to_vertex_positions;
	int* pointer_to_index_triangles;
	float* pointer_to_colors;
	float* pointer_to_texture;
	GLuint nb_indices;
	GLuint nb_points_buffer;
	std::vector<float> normals;
	std::vector<bool> front_face_triangles;
	std::vector<bool> inside_frustum_triangles;
	std::vector<bool> first_plane_triangles;
	std::vector<float> near_projected_vertex_positions;
	std::vector<bool> triangles_to_show;
	std::vector<int> index_temp;
//	std::vector<float> vertices_temp;
	GLdouble plane_coefficients[6][4];
	std::vector<bool> triangles_to_show_t1;
	std::vector<bool> triangles_to_show_t2;
	GLuint render_programID;
	std::vector<int> triangles_status;
	HalfedgeMesh halfedgeMesh;
	std::list<FaceIter> frontline;
	std::vector<int> frontline_colors;
	std::vector<float> true_vertex;
	std::vector<float> predicted_vertex;
	GLuint textureID;
	GLuint Texture;
	bool recording = false;
	bool mix = true;
} variable_to_share;

#endif // VARIABLETOSHARE_HPP
