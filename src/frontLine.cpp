#include "include/frontLine.hpp"

std::vector<int> getFrontLine(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles)
{
	std::vector<FaceIter> frontLine;
	std::list<MR_Face> multi_res_connectivity;
	HalfedgeMesh halfedgeMesh;
	halfedgeMesh.build(vertex_positions, index_triangles, multi_res_connectivity);
	for (FaceIter f = halfedgeMesh.facesBegin(); f != halfedgeMesh.facesEnd(); f++)
	{
		HalfedgeIter h = f -> halfedge();
		HalfedgeIter h_cur = h;
		do
		{
			if (!h->twin()->face()->isBoundary())
			{
				if(std::distance(halfedgeMesh.facesBegin(), h -> twin() -> face()) >= triangles_status.size())
					std::cout << "pas bon" << std::endl;
				if (triangles_status[std::distance(halfedgeMesh.facesBegin(), h -> twin() -> face())] == 1)
				{
					frontLine.push_back(f);
					break;
				}
			}
			h_cur = h_cur -> next();
		} while (h_cur == h);
	}
}

