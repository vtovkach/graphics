#pragma once

#include "mat4.hpp"

namespace Transform
{
    Mat4 translateTransform(float x, float y, float z);

    Mat4 scaleTransform(float sx, float sy, float sz);

    Mat4 rotationXTransform(float theta);

    Mat4 rotationYTransform(float theta);

    Mat4 rotationZTransform(float theta);

    Mat4 viewportTransform(int width, int height);
    
    Mat4 projectionTransform(float fov, float aspectRatio, float fNear, float fFar);
};