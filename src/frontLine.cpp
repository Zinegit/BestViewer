#include "include/frontLine.hpp"

std::vector<FaceIter> getFrontLine(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors)
{
	frontline_colors.resize(triangles_status.size(), 0);
	std::vector<FaceIter> frontline;
	std::list<MR_Face> multi_res_connectivity;
	HalfedgeMesh halfedgeMesh;
	halfedgeMesh.build(vertex_positions, index_triangles, multi_res_connectivity);
	int counter = 0;
	for (FaceIter f = halfedgeMesh.facesBegin(); f != halfedgeMesh.facesEnd(); f++,++counter)
	{
		if(triangles_status[counter] != 1)
		{
			HalfedgeIter h = f->halfedge();
			HalfedgeIter h_cur = h;
			do
			{
				if (!h_cur->twin()->face()->isBoundary())
				{
					if (triangles_status[std::distance(halfedgeMesh.facesBegin(), h_cur->twin()->face())] == 1)
					{
						frontline.push_back(f);
						frontline_colors[counter] = 1;
						break;
					}
				}
				h_cur = h_cur->next();
			} while (h_cur != h);
		}
	}
	return frontline;
}

