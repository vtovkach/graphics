#pragma once

#include "vec4.hpp"

struct Triangle
{
    Vec4 vertices[3];
    Vec4 norm; 

    Triangle(Vec4 A, Vec4 B, Vec4 C);
};