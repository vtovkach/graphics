#pragma once

#include "mat4.hpp"

namespace Transform
{
    Mat4 translate(float x, float y, float z);

    Mat4 scale(float sx, float sy, float sz);

    Mat4 rotationX(float theta);

    Mat4 rotationY(float theta);

    Mat4 rotationZ(float theta);

    Mat4 viewportTransform(int width, int height);
    
    Mat4 projectionTransform(float fov, float aspectRatio, float fNear, float fFar);
};