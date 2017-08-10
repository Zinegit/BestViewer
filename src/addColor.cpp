/**
 * \file addColor.cpp
 * \brief This function returns a vector of color to visualize which triangle appears, disappears, stays in the same state or belongs to frontline.
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include "include/addColor.hpp"

/**
 * \fn std::vector<float> colorize(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors)
 * \brief Function used to create the vector filled with the color of each vertex that is to be displayed in the viewer
 * \param triangles_status : State of every triangle (appeared/disappeared/same state)
 * \param vertex_positions : Geometrical description of the object
 * \param index_triangles : Topological description of the object
 * \param frontline_colors : The triangles that belong to the frontline
 * \return Vector filled with the color of each vertex of the object.
 */
std::vector<float> colorize(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors)
{
	std::vector<float> colors(vertex_positions.size(), 1.0);
	for(int i = 0; i < triangles_status.size(); i++)
	{
		// If triangle's state does not change, color is white
		if (triangles_status[i] == 0)
		{
			// If the vertex color is already blue then do not change anything
			if (!(colors[3 * index_triangles[3 * i]] == 0 && colors[3 * index_triangles[3 * i] + 1] == 0 && colors[3 * index_triangles[3 * i] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i]] = 1.0;
				colors[3 * index_triangles[3 * i] + 1] = 1.0;
				colors[3 * index_triangles[3 * i] + 2] = 1.0;
			}

			if (!(colors[3 * index_triangles[3 * i + 1]] == 0 && colors[3 * index_triangles[3 * i + 1] + 1] == 0 && colors[3 * index_triangles[3 * i + 1] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i + 1]] = 1.0;
				colors[3 * index_triangles[3 * i + 1] + 1] = 1.0;
				colors[3 * index_triangles[3 * i + 1] + 2] = 1.0;
			}

			if (!(colors[3 * index_triangles[3 * i + 2]] == 0 && colors[3 * index_triangles[3 * i + 2] + 1] == 0 && colors[3 * index_triangles[3 * i + 2] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i + 2]] = 1.0;
				colors[3 * index_triangles[3 * i + 2] + 1] = 1.0;
				colors[3 * index_triangles[3 * i + 2] + 2] = 1.0;
			}
		}
		// If triangle appears, color is green
		else if (triangles_status[i] == 1)
		{
			if (!(colors[3 * index_triangles[3 * i]] == 0 && colors[3 * index_triangles[3 * i] + 1] == 0 && colors[3 * index_triangles[3 * i] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i]] = 0;
				colors[3 * index_triangles[3 * i] + 1] = 1.0;
				colors[3 * index_triangles[3 * i] + 2] = 0;
			}

			if (!(colors[3 * index_triangles[3 * i + 1]] == 0 && colors[3 * index_triangles[3 * i + 1] + 1] == 0 && colors[3 * index_triangles[3 * i + 1] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i + 1]] = 0;
				colors[3 * index_triangles[3 * i + 1] + 1] = 1.0;
				colors[3 * index_triangles[3 * i + 1] + 2] = 0;
			}

			if (!(colors[3 * index_triangles[3 * i + 2]] == 0 && colors[3 * index_triangles[3 * i + 2] + 1] == 0 && colors[3 * index_triangles[3 * i + 2] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i + 2]] = 0;
				colors[3 * index_triangles[3 * i + 2] + 1] = 1.0;
				colors[3 * index_triangles[3 * i + 2] + 2] = 0;
			}
		}
		// If triangle disappears, color is red
		else if (triangles_status[i] == 2)
		{
			if (!(colors[3 * index_triangles[3 * i]] == 0 && colors[3 * index_triangles[3 * i] + 1] == 0 && colors[3 * index_triangles[3 * i] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i]] = 1.0;
				colors[3 * index_triangles[3 * i] + 1] = 0;
				colors[3 * index_triangles[3 * i] + 2] = 0;
			}

			if (!(colors[3 * index_triangles[3 * i + 1]] == 0 && colors[3 * index_triangles[3 * i + 1] + 1] == 0 && colors[3 * index_triangles[3 * i + 1] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i + 1]] = 1.0;
				colors[3 * index_triangles[3 * i + 1] + 1] = 0;
				colors[3 * index_triangles[3 * i + 1] + 2] = 0;
			}

			if (!(colors[3 * index_triangles[3 * i + 2]] == 0 && colors[3 * index_triangles[3 * i + 2] + 1] == 0 && colors[3 * index_triangles[3 * i + 2] + 2] == 1.0))
			{
				colors[3 * index_triangles[3 * i + 2]] = 1.0;
				colors[3 * index_triangles[3 * i + 2] + 1] = 0;
				colors[3 * index_triangles[3 * i + 2] + 2] = 0;
			}
		}
		if (frontline_colors[i] == 1)
		{
			colors[3 * index_triangles[3 * i]] = 0;
			colors[3 * index_triangles[3 * i] + 1] = 0;
			colors[3 * index_triangles[3 * i] + 2] = 1.0;

			colors[3 * index_triangles[3 * i + 1]] = 0;
			colors[3 * index_triangles[3 * i + 1] + 1] = 0;
			colors[3 * index_triangles[3 * i + 1] + 2] = 1.0;

			colors[3 * index_triangles[3 * i + 2]] = 0;
			colors[3 * index_triangles[3 * i + 2] + 1] = 0;
			colors[3 * index_triangles[3 * i + 2] + 2] = 1.0;
		}
	}
	return colors;
}
