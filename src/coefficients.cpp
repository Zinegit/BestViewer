#include "include/coefficients.hpp"

void findCoefficients(std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& triangles_status, HalfedgeMesh& halfedgeMesh, int depth)
{
	std::vector<FaceIter> children;
	for (FaceIter f = halfedgeMesh.facesBegin(); f != halfedgeMesh.facesEnd(); f++)
	{
		children = f->children();
		std::cout << children.size() << std::endl;
		HalfedgeIter h = f->halfedge();
		HalfedgeIter h_cur = h;
		do
		{
			std::list<FaceIter> frontline;
			std::vector<FaceIter> children_to_predict = h_cur->twin()->face()->children();
			for (int i = 0; i < children.size(); i++)
			{
				HalfedgeIter h_c = children[i]->halfedge();
				HalfedgeIter h_c_cur = h_c;
				do
				{
					if (std::find(children_to_predict.begin(), children_to_predict.end(), h_c_cur->twin()->face()) != children_to_predict.end());
					{
						frontline.push_back(children[i]);
						break;
					}
					h_c_cur = h_c_cur->next();
				} while (h_c_cur != h_c);
			}
			std::vector<float> dist_true_predicted;
			std::vector<float> predicted_vertices;
			std::vector<float> true_vertices;
			while (!frontline.empty())
			{
				HalfedgeIter h_c = frontline.front()->halfedge();
				HalfedgeIter h_c_cur = h_c;
				int dist2 = std::distance(halfedgeMesh.facesBegin(), frontline.front());
				do
				{
					int dist1 = std::distance(halfedgeMesh.facesBegin(), h_c_cur->twin()->face());
					if (std::find(children_to_predict.begin(), children_to_predict.end(), h_c_cur->twin()->face()) != children_to_predict.end() && triangles_status[dist1])
					{
						true_vertices.push_back(vertex_positions[3 * index_triangles[3 * dist1]]);
						true_vertices.push_back(vertex_positions[3 * index_triangles[3 * dist1] + 1]);
						true_vertices.push_back(vertex_positions[3 * index_triangles[3 * dist1] + 2]);
						std::vector<float> pos = predictTriangle(h_cur);
						predicted_vertices.push_back(pos[9]);
						predicted_vertices.push_back(pos[10]);
						predicted_vertices.push_back(pos[11]);
						frontline.push_back(h_c_cur->twin()->face());
						triangles_status[dist1] = 0;
						h_c_cur = h_c_cur->next();
					}
				} while (h_c_cur != h_c);
				frontline.pop_front();
			}
			for (int i = 0; i < predicted_vertices.size(); i += 3)
			{
				float dist = std::sqrt(std::pow(true_vertices[i] - predicted_vertices[i], 2) + std::pow(true_vertices[i+1] - predicted_vertices[i+1], 2) + std::pow(true_vertices[i+2] - predicted_vertices[i+2], 2));
				dist_true_predicted.push_back(dist);
			}
			exportToTxt(dist_true_predicted, "../analyses/data.txt");
			h_cur = h_cur->next();
		} while (h_cur != h);
	}
}
