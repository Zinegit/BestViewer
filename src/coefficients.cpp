#include "include/coefficients.hpp"

void findCoefficients(std::vector<float>& vertices, std::vector<int>& indices, HalfedgeMesh& old_halfedgeMesh, HalfedgeMesh& halfedgeMesh, int depth)
{
	for (FaceIter f = halfedgeMesh.facesBegin(); f != halfedgeMesh.facesEnd(); f++)
	{
		f->unmark();
	}
	for (VertexIter v = halfedgeMesh.verticesBegin(); v != halfedgeMesh.verticesEnd(); v++)
	{
		v->unmark();
	}

	for (FaceIter f = old_halfedgeMesh.facesBegin(); f != old_halfedgeMesh.facesEnd(); f++)
	{
		std::vector<FaceIter> children;
		FaceIter new_face = halfedgeMesh.facesBegin();
		std::advance(new_face, f->index());

		children = new_face->getChildren(depth);

		new_face = halfedgeMesh.facesBegin();
		std::advance(new_face, f->index());

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

				for(FaceIter child : children_to_predict)
				{
					child->mark();
					HalfedgeIter h_tmp = child->halfedge();
					do
					{
						if(h_tmp->vertex()->depth() > 0)
						{
							h_tmp->vertex()->mark();
						}
						h_tmp = h_tmp->next();
					} while(h_tmp != child->halfedge());
				}

				for(FaceIter child : children)
				{
					HalfedgeIter h_tmp = child->halfedge();
					do
					{
						h_tmp->vertex()->unmark();
						h_tmp = h_tmp->next();
					} while(h_tmp != child->halfedge());
				}

				neighbor_new_face = halfedgeMesh.facesBegin();
				std::advance(neighbor_new_face, h_cur->twin()->face()->index());

				// Go through every child of our main face to see if they belong to its frontline
				for (int i = 0; i < children.size(); i++)
				{
					HalfedgeIter h_c = children[i]->halfedge();
					HalfedgeIter h_c_cur = h_c;
					do
					{
						if(!h_cur->twin()->face()->isBoundary())
						{

							if (h_c_cur->twin()->face()->isMarked())
							{
								frontline.push_back(children[i]);
								break;
							}
						}
						h_c_cur = h_c_cur->next();
					} while (h_c_cur != h_c);
				}

				std::vector<std::tuple<int, float, float, float>> coefficients;
				std::vector<float> true_vertices;
				while (!frontline.empty())
				{
					HalfedgeIter h_c = frontline.front()->halfedge();
					HalfedgeIter h_c_cur = h_c;
					do
					{						
						if(!h_c_cur->twin()->face()->isBoundary() && h_c_cur->twin()->face()->isMarked())
						{
							HalfedgeIter reference_halfedge = h_c_cur->next()->next();
							HalfedgeIter halfedge_to_predict = h_c_cur->twin()->next()->next();

							if(halfedge_to_predict->vertex()->isMarked())
							{
								true_vertices.push_back(vertices[3 * halfedge_to_predict->vertex()->index()]);
								true_vertices.push_back(vertices[3 * halfedge_to_predict->vertex()->index() + 1]);
								true_vertices.push_back(vertices[3 * halfedge_to_predict->vertex()->index() + 2]);
								std::vector<float> pos = predictTriangle(reference_halfedge);
								coefficients.push_back(std::make_tuple(halfedge_to_predict->vertex()->index(), pos[9], pos[10], pos[11]));
								halfedge_to_predict->vertex()->unmark();
							}

							halfedge_to_predict->face()->unmark();

							HalfedgeIter h_tmp = halfedge_to_predict;
							do
							{
								if(!h_tmp->twin()->face()->isBoundary() && h_tmp->twin()->face()->isMarked())
								{
									frontline.push_back(h_tmp->face());
								}
								h_tmp = h_tmp->next();
							} while(h_tmp!= halfedge_to_predict);
						}
						h_c_cur = h_c_cur->next();
					} while (h_c_cur != h_c);
					frontline.pop_front();

				}
				for (int i = 0; i < coefficients.size(); ++i)
				{
					std::get<1>(coefficients[i]) = true_vertices[i] - std::get<1>(coefficients[i]);
					std::get<2>(coefficients[i]) = true_vertices[i] - std::get<2>(coefficients[i]);
					std::get<3>(coefficients[i]) = true_vertices[i] - std::get<3>(coefficients[i]);
				}
				// Generate the file name
				// The standard form is: "index_of_the_known_triangle" + "_" + "index_of_the_triangle_to_predict"
				std::string target_file = "../analyses/";
				target_file += std::to_string(new_face->index());
				target_file += "_";
				target_file += std::to_string(neighbor_new_face->index());
				target_file += ".txt";
				exportToTxt(coefficients, target_file);
			} else {

			}
			h_cur = h_cur->next();
		} while (h_cur != h);
	}
}
