/**
 * \file appearance.cpp
 * \brief Return a list representing which triangle appears/disappears or stay in the same state.
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#include <iostream>
#include "include/appearance.hpp"

/**
 * \fn std::vector<int> appearance(std::vector<bool>& triangles_to_show_t1, std::vector<bool>& triangles_to_show_t2)
 * \brief This function compares the triangles visible at t1 and t2 and return a vector discribing which ones disappeared/appeared or stayed in the same state
 * \param triangles_to_show_t1 : vector showing which triangle is visible or not at t1
 * \param triangles_to_show_t2 : vector showing which triangle is visible or not at t2
 * \return The vector discribing if a triangle appears/disappears/stays in the same state
 */
std::vector<int> appearance(std::vector<bool>& triangles_to_show_t1, std::vector<bool>& triangles_to_show_t2)
{
	std::vector<int> appearing_triangles;
	appearing_triangles.reserve(triangles_to_show_t1.size());
	for (int i = 0; i < triangles_to_show_t1.size(); i++)
	{
		if (triangles_to_show_t1[i] == 0 && triangles_to_show_t2[i] == 1)
		{
			appearing_triangles.push_back(1);
		}
		else if (triangles_to_show_t1[i] == 1 && triangles_to_show_t2[i] == 0)
		{
			appearing_triangles.push_back(2);
		}
		else if (triangles_to_show_t1[i] == triangles_to_show_t2[i])
		{
			appearing_triangles.push_back(0);
		}
	}
	return appearing_triangles;
}
