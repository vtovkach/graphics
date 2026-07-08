#pragma once

struct Vec4
{
    float x, y, z, w; 

    Vec4();
    Vec4(float x, float y, float z, float w);
    
    const float& operator[](int i) const;
    float& operator[](int i);

    static Vec4 normalizeVec(Vec4 a);
    static Vec4 crossProduct(Vec4 a, Vec4 b);
    static float dotProduct(Vec4 a, Vec4 b);
};