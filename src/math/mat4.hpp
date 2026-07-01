#pragma once

#include "math.hpp"

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
    
    static Mat4 convertVectors(Vec4 a, Vec4 b, Vec4 c, Vec4 d);
    static Mat4 convertVectors(Vec4 a, Vec4 b, Vec4 c);

    static Mat4 translate(float x, float y, float z);
    static Mat4 scale(float sx, float sy, float sz);
    static Mat4 rotationX(float theta);
    static Mat4 rotationY(float theta);
    static Mat4 rotationZ(float theta);
    static Mat4 viewportTransform(int width, int height);
    static Mat4 projectionTransform(float fov, float aspectRatio, float fNear, float fFar);


private:
    static constexpr int N = 4; 
    float mat4[4][4];
};