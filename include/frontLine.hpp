#ifndef FRONTLINE_H
#define FRONTLINE_H

#include <vector>
#include "external/I3S-Meshing/include/halfedgemesh.h"

std::vector<int> getFrontLine(std::vector<int>& triangle_status, std::vector<float>& vertex_positions, std::vector<int>& index_positions);


#endif // FRONTLINE_H
