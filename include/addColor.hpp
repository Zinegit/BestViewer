#include <vector>
#include <iostream>

/**
*  \brief Coloration de l'objet visualisé

*  \param triangle_status: état de ca
*  \return true si morceau deja present dans la liste,
*  false sinon
*/

std::vector<float> colorize(std::vector<int>& triangles_status, std::vector<float>& vertex_positions, std::vector<int>& index_triangles, std::vector<int>& frontline_colors);
