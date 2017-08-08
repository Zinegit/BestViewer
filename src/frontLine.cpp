/**
 * \file frontLine.cpp
 * \brief Return faces of every triangle belonging to the frontline.
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/frontLine.hpp"

/**
 * \fn void updateFrontLine(std::list<FaceIter> frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function updates the frontline untill every triangle is predicted
 * \param frontline : The initialized frontline of the object
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline are associated with one in order to colorize them in blue in addColor
 * \return void
 */

std::vector<float> updateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
{
	std::vector<float> predicted_vertices;
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
					std::vector<float> pos = predictTriangle(frontline.front(), h_cur, halfedgeMesh);
					predicted_vertices.push_back(pos[0]);
					predicted_vertices.push_back(pos[1]);
					predicted_vertices.push_back(pos[2]);
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
	return predicted_vertices;
}

/**
 * \fn void TempUpdateFrontLine(std::list<FaceIter> frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function updates the frontline triangle by triangle
 * \param frontline : The initialized frontline of the object
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline are associated with one in order to colorize them in blue in addColor
 * \return void
 */

void TempUpdateFrontLine(std::list<FaceIter>& frontline, std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
{
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
				std::vector<float> predicted_vertex = predictTriangle(frontline.front(), h_cur, halfedgeMesh);
				std::cout << predicted_vertex[0] << " " << predicted_vertex[1] << " " << predicted_vertex[2] << std::endl;
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

/**
 * \fn std::vector<FaceIter> getFrontLine(std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function returns a vector of faces that belong to the frontline using the halfedge structure
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline
 * \return a vector of the faces that belong to the frontline
 */

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

/**
 * \fn std::vector<FaceIter> getFrontLine(std::vector<int>& triangles_status, std::vector<int>& frontline_colors, HalfedgeMesh& halfedgeMesh)
 * \brief This function returns a vector of faces that belong to the frontline using the halfedge structure
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline
 * \return a vector of the faces that belong to the frontline
 */

std::vector<float> predictTriangle(FaceIter& frontline_triangle, HalfedgeIter& frontline_halfedge, HalfedgeMesh& halfedgeMesh)
{
	std::vector<float> pos(3, 0);
	VertexIter vec1 = frontline_halfedge->vertex();
	VertexIter vec2 = frontline_halfedge->next()->vertex();
	VertexIter vec3 = frontline_halfedge->next()->next()->vertex();
	pos[0] = vec1->x - 2*vec3->x + vec2->x;
	pos[1] = vec1->y - 2*vec3->y + vec2->y;
	pos[2] = vec1->z - 2*vec3->z + vec2->z;
	return pos;
}



