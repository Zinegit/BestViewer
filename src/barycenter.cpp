#include "include/barycenter.hpp"

const qglviewer::Vec barycenter(std::vector<float>& vertices)
{
    int nb_points = vertices.size();
    float X = 0;
    for (int i = 0; i < nb_points; i += 3)
        X += vertices[i];
    float X_mean = X / (nb_points / 3);
    float Y = 0;
    for (int i = 1; i < nb_points; i += 3)
        Y += vertices[i];
    float Y_mean = Y / (nb_points / 3);
    float Z = 0;
    for (int i = 2; i < nb_points; i += 3)
        Z += vertices[i];
    float Z_mean = Z / (nb_points / 3);
    const qglviewer::Vec bar(X_mean, Y_mean, Z_mean);
    return bar;

}
