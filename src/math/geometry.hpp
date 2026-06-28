#pragma once

#include <vector>
#include "math.hpp"

struct Triangle
{
    Vec4 vertices[3];
};

struct Mesh
{
    std::vector<Triangle> triangles; 
};