/**
 * \file toTxt.hpp
 * \brief Used for exporting data into files
 * \author Tom Mourot-Faraut
 * \version 1.0
 */

#ifndef TOTXT_HPP
#define TOTXT_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <tuple>

#include "include/statistics.hpp"

/**
 * \fn void exportToTxt(std::vector<std::tuple<int, float, float, float>> coefficients,  std::string target_file);
 * \brief This function exports the data collected into a file
 * \param coefficients : The index of the vertex + The distance between the predicted and the real position of each vertex
 * \param target_file : The file in which the values will be written
 * \return void
 */
void exportToTxt(std::vector<std::tuple<int, float, float, float>> coefficients,  std::string target_file);

#endif // TOTXT_HPP
