#ifndef FRONTLINE_H
#define FRONTLINE_H

#include <vector>
#include "external/I3S-Meshing/include/halfedgemesh.h"

std::vector<float> updateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

void TempUpdateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

std::list<FaceIter> getFrontLine(std::vector<int>& triangle_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh);

std::vector<float> predictTriangle(FaceIter& frontline_triangle, HalfedgeIter& frontline_halfedge, HalfedgeMesh& halfedgeMesh);

#endif // FRONTLINE_H
