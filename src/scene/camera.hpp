#pragma once 

#include "math.hpp"

class Camera
{
public:
    bool doesTriangleFaceCamera(Triangle tri) const;

private:
    Vec4 cameraPosition = {0, 0, 0, 0}; 
};