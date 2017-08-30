#include "include/coefficients.hpp"

void findCoefficients(std::vector<float>& vertices, std::vector<int>& indices, std::vector<int>& triangles_status, HalfedgeMesh& old_halfedgeMesh, HalfedgeMesh& halfedgeMesh, int depth)
{
	std::vector<FaceIter> children;
	for (FaceIter f = old_halfedgeMesh.facesBegin(); f != old_halfedgeMesh.facesEnd(); f++)
	{
		FaceIter new_face = halfedgeMesh.facesBegin();
		std::advance(new_face, f->index());

		children = new_face->getChildren(depth);

//		for(auto&& child : children)
//		{
//			std::cout << child->index() << std::endl;
//		}

		HalfedgeIter h = f->halfedge();
		HalfedgeIter h_cur = h;
		do
		{
			std::list<FaceIter> frontline;

			FaceIter neighbor_new_face = halfedgeMesh.facesBegin();

			if(!h_cur->twin()->face()->isBoundary())
			{

				std::advance(neighbor_new_face, h_cur->twin()->face()->index());

				std::vector<FaceIter> children_to_predict = neighbor_new_face->getChildren(depth);
				// Go through every child of our main face to see if it belongs to its frontline
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
	//				int dist2 = std::distance(halfedgeMesh.facesBegin(), frontline.front());
					do
					{
						int dist1 = std::distance(halfedgeMesh.facesBegin(), h_c_cur->twin()->face());
						if ((std::find(children_to_predict.begin(), children_to_predict.end(), h_c_cur->twin()->face()) != children_to_predict.end()) && (triangles_status[dist1] == 1))
						{
							true_vertices.push_back(vertices[3 * indices[3 * dist1]]);
							true_vertices.push_back(vertices[3 * indices[3 * dist1] + 1]);
							true_vertices.push_back(vertices[3 * indices[3 * dist1] + 2]);
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
				// Generate the file name
				// The standard form is: "index_of_the_known_triangle" + "_" + "index_of_the_triangle_to_predict"
				std::string target_file = "../analyses/";
				target_file += std::to_string(f->index());
				target_file += "_";
				target_file += std::to_string(new_face->index());
				target_file += ".txt";
				exportToTxt(dist_true_predicted, target_file);
			}
			h_cur = h_cur->next();
		} while (h_cur != h);
	}
}
//	for (FaceIter f = halfedgeMesh.facesBegin(); f != halfedgeMesh.facesEnd(); f++)
//	{
//			children = f->getChildren(depth);
//			HalfedgeIter h = f->halfedge();
//			HalfedgeIter h_cur = h;
//			do
//			{
//				std::list<FaceIter> frontline;
//				std::vector<FaceIter> children_to_predict = h_cur->twin()->face()->getChildren(depth);
//				for (int i = 0; i < children.size(); i++)
//				{
//					HalfedgeIter h_c = children[i]->halfedge();
//					HalfedgeIter h_c_cur = h_c;
//					do
//					{
//						if (std::find(children_to_predict.begin(), children_to_predict.end(), h_c_cur->twin()->face()) != children_to_predict.end());
//						{
//							frontline.push_back(children[i]);
//							break;
//						}
//						h_c_cur = h_c_cur->next();
//					} while (h_c_cur != h_c);
//				}
//				std::vector<float> dist_true_predicted;
//				std::vector<float> predicted_vertices;
//				std::vector<float> true_vertices;
//				while (!frontline.empty())
//				{
//					HalfedgeIter h_c = frontline.front()->halfedge();
//					HalfedgeIter h_c_cur = h_c;
//					int dist2 = std::distance(halfedgeMesh.facesBegin(), frontline.front());
//					do
//					{
//						int dist1 = std::distance(halfedgeMesh.facesBegin(), h_c_cur->twin()->face());
//						if (std::find(children_to_predict.begin(), children_to_predict.end(), h_c_cur->twin()->face()) != children_to_predict.end() && triangles_status[dist1] == 1)
//						{
//							true_vertices.push_back(vertices[3 * indices[3 * dist1]]);
//							true_vertices.push_back(vertices[3 * indices[3 * dist1] + 1]);
//							true_vertices.push_back(vertices[3 * indices[3 * dist1] + 2]);
//							std::vector<float> pos = predictTriangle(h_cur);
//							predicted_vertices.push_back(pos[9]);
//							predicted_vertices.push_back(pos[10]);
//							predicted_vertices.push_back(pos[11]);
//							frontline.push_back(h_c_cur->twin()->face());
//							triangles_status[dist1] = 0;
//							h_c_cur = h_c_cur->next();
//						}
//					} while (h_c_cur != h_c);
//					frontline.pop_front();
//				}
//				for (int i = 0; i < predicted_vertices.size(); i += 3)
//				{
//					float dist = std::sqrt(std::pow(true_vertices[i] - predicted_vertices[i], 2) + std::pow(true_vertices[i+1] - predicted_vertices[i+1], 2) + std::pow(true_vertices[i+2] - predicted_vertices[i+2], 2));
//					dist_true_predicted.push_back(dist);
//				}
//				exportToTxt(dist_true_predicted, "../analyses/data.txt");
//				h_cur = h_cur->next();
//			} while (h_cur != h);
//	}
//}
