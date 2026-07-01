#pragma once

#include "vec4.hpp"

class Mat4
{
public:
    Mat4();

    void setElement(int row, int column, float data);

    float getElement(int row, int column) const;

    Mat4 operator*(const Mat4& other) const; 
    Vec4 operator*(const Vec4& other) const;
    Mat4 operator+(const Mat4& other) const; 
    
    void toVectors(Vec4& a, Vec4& b, Vec4& c);

private:
    static constexpr int N = 4; 
    float mat4[4][4];
};