#include "include/frontLine.hpp"

std::vector<float> updateFrontLine(std::list<FaceIter>& frontline,
								   std::vector<int>& triangles_status,
								   std::vector<int>& frontline_colors,
								   std::vector<float>& vertices,
								   std::vector<int>& indices,
								   HalfedgeMesh& halfedgeMesh)
{
	std::vector<float> dist_true_predicted;
	std::vector<float> predicted_vertices;
	std::vector<float> true_vertices;
	while (!frontline.empty())
	{
		HalfedgeIter h = frontline.front()->halfedge();
		HalfedgeIter h_cur = h;
		int dist2 = std::distance(halfedgeMesh.facesBegin(), frontline.front());
		do
		{
			// If a halfedge is a boundary, the triangle it belongs to is not part of the frontline
			if (!h_cur->twin()->face()->isBoundary())
			{
				int dist1 = std::distance(halfedgeMesh.facesBegin(), h_cur->twin()->face());
				int status = triangles_status[dist1];
				// If the triangle next to the current triangle appeared, then the current triangle belongs to the front line
				if (status == 1)
				{
					true_vertices.push_back(vertices[3 * indices[3 * dist1]]);
					true_vertices.push_back(vertices[3 * indices[3 * dist1] + 1]);
					true_vertices.push_back(vertices[3 * indices[3 * dist1] + 2]);
					std::vector<float> pos = predictTriangle(h_cur);
					predicted_vertices.push_back(pos[9]);
					predicted_vertices.push_back(pos[10]);
					predicted_vertices.push_back(pos[11]);
					frontline.push_back(h_cur->twin()->face());
					frontline_colors[dist1] = 1;
					triangles_status[dist1] = 0;
				}
				frontline_colors[dist2] = 0;
			}
			h_cur = h_cur->next();
		} while (h_cur != h);
		frontline.pop_front();
	}
	for (int i = 0; i < predicted_vertices.size(); i += 3)
	{
		float dist = std::sqrt(std::pow(true_vertices[i] - predicted_vertices[i], 2) + std::pow(true_vertices[i+1] - predicted_vertices[i+1], 2) + std::pow(true_vertices[i+2] - predicted_vertices[i+2], 2));
		dist_true_predicted.push_back(dist);
	}
	return dist_true_predicted;
}

float TempUpdateFrontLine(std::list<FaceIter>& frontline,
						  std::vector<int>& triangles_status,
						  std::vector<float>& vertex_positions,
						  std::vector<int>& index_triangles,
						  std::vector<int>& frontline_colors,
						  HalfedgeMesh& halfedgeMesh,
						  std::vector<float>& true_vertex,
						  std::vector<float>& predicted_vertex)
{
	float dist_true_predicted;
	HalfedgeIter h = frontline.front()->halfedge();
	HalfedgeIter h_cur = h;
	int dist2 = std::distance(halfedgeMesh.facesBegin(), frontline.front());
	do
	{
		// If an halfedge is a boundary, the triangle it belongs to is not part of the frontline
		if (!h_cur->twin()->face()->isBoundary())
		{
			int dist1 = std::distance(halfedgeMesh.facesBegin(), h_cur->twin()->face());
			int status = triangles_status[dist1];
			// If the triangle next to the current triangle appeared, then the current triangle belongs to the front line
			if (status == 1)
			{
				true_vertex[0] = vertex_positions[3 * index_triangles[3 * dist1]];
				true_vertex[1] = vertex_positions[3 * index_triangles[3 * dist1] + 1];
				true_vertex[2] = vertex_positions[3 * index_triangles[3 * dist1] + 2];
				predicted_vertex = predictTriangle(h_cur);
				frontline.push_back(h_cur->twin()->face());
				frontline_colors[dist1] = 1;
				triangles_status[dist1] = 0;
				dist_true_predicted = std::sqrt(std::pow(true_vertex[0] - predicted_vertex[9], 2) + std::pow(true_vertex[1] - predicted_vertex[10], 2) + std::pow(true_vertex[2] - predicted_vertex[11], 2));
			}
			frontline_colors[dist2] = 0;
		}
		h_cur = h_cur->next();
	} while (h_cur != h);
	frontline.pop_front();
	return dist_true_predicted;
}

std::list<FaceIter> getFrontLine(std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
{
	frontline_colors.resize(triangles_status.size(), 0);
	std::list<FaceIter> frontline;
	int counter = 0;
	for (FaceIter f = halfedgeMesh.facesBegin(); f != halfedgeMesh.facesEnd(); f++, counter++)
	{
		// If the triangle appeared, it does not belong to the front line
		if(triangles_status[counter] != 1)
		{
			HalfedgeIter h = f->halfedge();
			HalfedgeIter h_cur = h;
			do
			{
				// If an halfedge is a boundary, the triangle it belongs to is not part of the front line
				if (!h_cur->twin()->face()->isBoundary())
				{
					// If the triangle next to the current triangle appeared, then the current triangle belongs to the front line
					if (triangles_status[std::distance(halfedgeMesh.facesBegin(), h_cur->twin()->face())] == 1)
					{
						frontline.push_back(f);
						frontline_colors[counter] = 1;
						break;
					}
					frontline_colors[counter] = 0;
				}
				h_cur = h_cur->next();
			} while (h_cur != h);
		}
	}
	return frontline;
}

std::vector<float> predictTriangle(HalfedgeIter& frontline_halfedge)
{
	std::vector<float> pos(12, 0);
	VertexIter vec1 = frontline_halfedge->vertex();
	VertexIter vec2 = frontline_halfedge->next()->vertex();
	VertexIter vec3 = frontline_halfedge->next()->next()->vertex();
	// For debugging use
	pos[0] = vec1->x;
	pos[1] = vec1->y;
	pos[2] = vec1->z;
	pos[3] = vec3->x;
	pos[4] = vec3->y;
	pos[5] = vec3->z;
	pos[6] = vec2->x;
	pos[7] = vec2->y;
	pos[8] = vec2->z;
	// For debugging use
	pos[9] = vec1->x + vec2->x - vec3->x;
	pos[10] = vec1->y + vec2->y - vec3->y;
	pos[11] = vec1->z + vec2->z - vec3->z;
	return pos;
}
