#pragma once 

#include <cmath>
#include <vector>

#include "vec4.hpp"
#include "mat4.hpp"
#include "transform.hpp"
#include "triangle.hpp"

constexpr float pi = 3.14159265359;

/* Move somewhere else later */
struct Mesh
{
    std::vector<Triangle> triangles; 
};