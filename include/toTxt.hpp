#ifndef TOTXT_H
#define TOTXT_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "include/statistics.hpp"

void exportToTxt(std::vector<float> dist_true_predicted,  std::string target_file);

#endif // TOTXT_H
