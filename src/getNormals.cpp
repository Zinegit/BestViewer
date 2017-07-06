#include "include/getNormals.hpp"
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
#include "external/I3S-Meshing/ply.h"
#include "external/I3S-Meshing/dat.h"

// Display elements of vectors
#include <vector>
#include <iostream>

#include <math.h>
#include <boost/geometry.hpp>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

vector<float> getNormals( vector<float>& vertex_positions, vector<int>& index_triangles)
{
    vector<float> normals(index_triangles.size(), 0);
    vector<float> a(3, 0);
    vector<float> b(3, 0);
    Eigen::Vector3d n;
    for (int i = 0; i < index_triangles.size(); i += 3 )
    {
        a[0] = vertex_positions[3 * index_triangles[i+1]] - vertex_positions[3 * index_triangles[i]];
        a[1] = vertex_positions[3 * index_triangles[i+1]+1] - vertex_positions[3 * index_triangles[i]+1];
        a[2] = vertex_positions[3 * index_triangles[i+1]+2] - vertex_positions[3 * index_triangles[i]+2];
        b[0] = vertex_positions[3 * index_triangles[i+2]] - vertex_positions[3 * index_triangles[i]];
        b[1] = vertex_positions[3 * index_triangles[i+2]+1] - vertex_positions[3 * index_triangles[i]+1];
        b[2] = vertex_positions[3 * index_triangles[i+2]+2] - vertex_positions[3 * index_triangles[i]+2];

        Eigen::Vector3d a_e(a[0], a[1], a[2]);
        Eigen::Vector3d b_e(b[0], b[1], b[2]);
        n = a_e.cross(b_e);
        normals[i] = n[0];
        normals[i+1] = n[1];
        normals[i+2] = n[2];
    }
    return normals;
}


