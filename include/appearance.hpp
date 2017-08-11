/**
 * \file appearance.hpp
 * \brief Return a list representing which triangle appears/disappears or stay in the same state.
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef APPEARANCE_HPP
#define APPEARANCE_HPP

#include <vector>

/**
 * \fn std::vector<int> appearance(std::vector<bool>& triangles_to_show_t1, std::vector<bool>& triangles_to_show_t2)
 * \brief This function compares the triangles visible at t1 and t2 and return a vector discribing which ones disappeared/appeared or stayed in the same state
 * \param triangles_to_show_t1 : vector showing which triangle is visible or not at t1
 * \param triangles_to_show_t2 : vector showing which triangle is visible or not at t2
 * \return The vector discribing if a triangle appears/disappears/stays in the same state
 */
std::vector<int> appearance(std::vector<bool>& triangles_to_show_t1, std::vector<bool>& triangles_to_show_t2);

#endif // APPEARANCE_HPP
