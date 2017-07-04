#include "include/crossProduct.hpp"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

vector<float> crossProduct(vector<float>& vector1, vector<float>& vector2)
{
    if (vector1.size() != vector2.size())
    {
            cerr << "Dimensions do not match" << endl;
            exit(-1);
    }
    vector<float> result(vector1.size(), 0);
    for (int i = 0; i < vector1.size(); i++)
    {
        result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
        result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
        result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
    }
   return result;
}
