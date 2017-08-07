#ifndef FRONTLINE_H
#define FRONTLINE_H

#include <vector>
#include "external/I3S-Meshing/include/halfedgemesh.h"

void updateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

void TempUpdateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

std::list<FaceIter> getFrontLine(std::vector<int>& triangle_status, std::vector<float>& vertex_positions, std::vector<int>& index_positions, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);



#endif // FRONTLINE_H
