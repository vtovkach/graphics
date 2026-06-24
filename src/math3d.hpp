#pragma once 

#include <vector>

struct vec3d
{
    float x,y,z;
};

struct mat4x4
{
    float m[4][4] = { 0 };
};

struct triangle
{
    vec3d vertices[3];
};

struct mesh
{
    std::vector<triangle> tris; 
};

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m);