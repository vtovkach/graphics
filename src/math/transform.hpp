#pragma once

#include "mat4.hpp"

namespace Transform
{
    Mat4 formMatrix(const Vec4& a, const Vec4& b, const Vec4& c);

    Mat4 translateTransform(float x, float y, float z);

    Mat4 scaleTransform(float sx, float sy, float sz);

    Mat4 rotationXTransform(float theta);

    Mat4 rotationYTransform(float theta);

    Mat4 rotationZTransform(float theta);

    Mat4 viewportTransform(int width, int height);
    
    Mat4 projectionTransform(float fov, float aspectRatio, float fNear, float fFar);

    Mat4 cameraTransform(Vec4 cameraPosition, Vec4 right, Vec4 up, Vec4 forward);
};