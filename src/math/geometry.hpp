#pragma once

#include <vector>
#include "math.hpp"

struct Triangle
{
    Vec4 vertices[3];
    Vec4 norm; 

    Triangle(Vec4 A, Vec4 B, Vec4 C);
};

struct Mesh
{
    std::vector<Triangle> triangles; 
};