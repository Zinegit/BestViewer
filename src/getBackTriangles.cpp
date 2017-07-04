// Include basic libraries
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

#include "include/simpleViewer.hpp"
#include "include/shader.hpp"
#include "include/barycentre.hpp"
#include "include/crossProduct.hpp"
#include "external/I3S-Meshing/ply.h"
#include "external/I3S-Meshing/dat.h"

// Display elements of vectors
#include <vector>
#include <iostream>

#include <math.h>
#include <boost/geometry.hpp>

using namespace std;

vector<int> getBackTriangles( vector<float> vertex_positions, vector<int> index_triangles)
{
    vector<int> normals(0);
    for (int i = 0; i < index_triangles.size(); i += 3 )
    {
        float n = vertex_positions[index_triangles[i]];
    }

    /* Test de CrossProduct
    vector<float> a(3, 0);
    a[0] = 2;
    a[1] = 1;
    a[2] = 3
    vector<float> b(3, 1);
    vector<float> c = crossProduct(a, b);
    for (auto v : c)
         cout << v << endl;
    */

    return normals;
}


