/**
 * \file statistics.hpp
 * \brief Gives some useful functions for statistical studies
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>
#include <numeric>

/**
 * \fn float mean(std::vector<float> dist_true_predicted)
 * \brief This function returns the mean of the distances between the predicted and the real position of each vertex
 * \param dist_true_predicted : The distance between the predicted and the real position of each vertex
 * \return The mean of all measures
 */
float mean(std::vector<float> dist_true_predicted);

#endif // STATISTICS_HPP
