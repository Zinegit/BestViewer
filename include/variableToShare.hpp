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
	std::vector<int> indices;
	std::vector<float> vertices;
	std::vector<int> old_indices;
	std::vector<float> old_vertices;
	std::vector <float> colors;
	std::vector <float> uvs;
	std::vector<float> indexed_vertices;
	std::vector<float> indexed_uvs;
	std::vector<int> indexed_indices;
	GLuint vertices_buffer;
	GLuint nb_vertices;
	GLuint nb_uvs;
	GLuint color_buffer;
	GLuint uvs_buffer;
	GLuint indices_buffer;
	GLuint nb_indices;
	std::vector<float> normals;
	int* pointer_to_indices;
	float* pointer_to_vertices;
	float* pointer_to_colors;
	float* pointer_to_uvs;
	bool mix = true;
	std::vector<bool> front_face_triangles;
	std::vector<bool> inside_frustum_triangles;
	std::vector<bool> first_plane_triangles;
	std::vector<float> near_projected_vertex_positions;
	std::vector<bool> triangles_to_show;
	std::vector<int> temp_indices;
	GLdouble plane_coefficients[6][4];
	std::vector<bool> triangles_to_show_t1;
	std::vector<bool> triangles_to_show_t2;
	GLuint render_programID;
	std::vector<int> triangles_status;
	bool recording = false;
	HalfedgeMesh halfedgeMesh;
	HalfedgeMesh old_halfedgeMesh;
	std::list<FaceIter> frontline;
	std::vector<int> frontline_colors;
	std::vector<float> true_vertex;
	std::vector<float> predicted_vertex;
	GLuint textureID;
	GLuint Texture;
	std::vector<float> vertices_in_order;
	int depth;
	int type_file;
} variable_to_share;

#endif // VARIABLETOSHARE_HPP
