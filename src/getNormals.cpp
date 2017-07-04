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

vector<float> getBackTriangles( vector<float>& vertex_positions, vector<int>& index_triangles)
{
    vector<float> normals(index_triangles.size(), 0);
    vector<float> a(3, 0);
    vector<float> b(3, 0);
    for (int i = 0; i < index_triangles.size(); i += 3 )
    {
        a[0] = vertex_positions[index_triangles[i]];
        a[1] = vertex_positions[index_triangles[i]+1];
        a[2] = vertex_positions[index_triangles[i]+2];
        b[0] = vertex_positions[index_triangles[i+1]];
        b[1] = vertex_positions[index_triangles[i+1]+1];
        b[2] = vertex_positions[index_triangles[i+1]+2];

        vector<float> n = crossProduct(a, b);
        normals[i] = n[0];
        normals[i+1] = n[1];
        normals[i+2] = n[2];
    }
    return normals;
}


