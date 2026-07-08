#include "v-math.hpp"

#include <cmath>
#include <stdexcept>

Vec4::Vec4() : x(0), y(0), z(0), w(0) {};

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

float& Vec4::operator[](int i)
{
    switch(i)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("Vec4 index");
    }
}

const float& Vec4::operator[](int i) const
{
    switch(i)
    {
        case 0: return x;
        case 1: return y;
        case 2: return z;
        case 3: return w;
        default: throw std::out_of_range("Vec4 index");
    }
}

Vec4 Vec4::crossProduct(Vec4 a, Vec4 b)
{
    return {(a.y*b.z) - (a.z*b.y), (a.z*b.x ) - (a.x*b.z), (a.x*b.y) - (a.y*b.x), 0.0f};
}

float Vec4::dotProduct(Vec4 a, Vec4 b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec4 Vec4::normalizeVec(Vec4 a)
{
    float mag = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));

    if(mag == 0.0f) return Vec4();
    
    return {a.x / mag, a.y / mag, a.z / mag, 0};
}