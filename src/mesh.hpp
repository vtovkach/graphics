#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "math3d.hpp"
#include <string>

struct triangle
{
    vec3d vertices[3];
};

struct mesh
{
    std::vector<triangle> tris;

    bool LoadFromObjFile(std::string filePath);
};
