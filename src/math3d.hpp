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

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m);

void CrossProduct(const vec3d &vec1, const vec3d &vec2, vec3d &o);