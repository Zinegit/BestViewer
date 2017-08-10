#ifndef FRONTLINE_H
#define FRONTLINE_H

#include <vector>
#include <GL/glew.h>
#include "external/I3S-Meshing/include/halfedgemesh.h"

std::vector<float> updateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, HalfedgeMesh& halfedgeMesh);

float TempUpdateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh, std::vector<float>& true_vertex, std::vector<float>& predicted_vertex);

std::list<FaceIter> getFrontLine(std::vector<int>& triangle_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

std::vector<float> predictTriangle(FaceIter& frontline_triangle, HalfedgeIter& frontline_halfedge, HalfedgeMesh& halfedgeMesh);

#endif // FRONTLINE_H
