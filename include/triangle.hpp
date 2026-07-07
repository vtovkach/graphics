#pragma once

#include "vec4.hpp"

struct Triangle
{
    Vec4 vertices[3];
    Mat4 matrixForm;
    Vec4 norm; 

    Triangle(Vec4 A, Vec4 B, Vec4 C);

    void transform(Mat4 transformation);
    void updateState();

    Mat4 getMatrixForm() const;

    Vec4 operator[](int i) const;
};