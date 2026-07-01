#include <cmath>
#include <stdexcept>
#include "math.hpp"

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

Mat4::Mat4() : mat4{}{};

void Mat4::setElement(int row, int column, float data)
{
    mat4[row][column] = data;
}

float Mat4::getElement(int row, int column)
{
    return mat4[row][column];
}

Mat4 Mat4::translate(float x, float y, float z)
{
    Mat4 translateTransform;

    // Set diagonals to 1
    translateTransform.setElement(0, 0, 1);
    translateTransform.setElement(1, 1, 1);
    translateTransform.setElement(2, 2, 1);
    translateTransform.setElement(3, 3, 1);

    // Set final column to object's world coordinates 
    translateTransform.setElement(0, 3, x);
    translateTransform.setElement(1, 3, y);
    translateTransform.setElement(2, 3, z);
    
    return translateTransform;
}

Mat4 Mat4::scale(float sx, float sy, float sz)
{
    Mat4 scaleTransform;

    scaleTransform.setElement(0, 0, sx);
    scaleTransform.setElement(1, 1, sy);
    scaleTransform.setElement(2, 2, sz);
    scaleTransform.setElement(3, 3, 1);

    return scaleTransform;
}

Mat4 Mat4::rotationX(float theta)
{
    Mat4 rotationX;

    float radians = theta * (pi / 180);
    float cos = cosf(radians);
    float sin = sinf(radians);

    rotationX.setElement(0, 0, 1.0f);
    rotationX.setElement(1, 1, cos);
    rotationX.setElement(1, 2, -sin);
    rotationX.setElement(2, 1, sin);
    rotationX.setElement(2, 2, cos);
    rotationX.setElement(3, 3, 1.0f);

    return rotationX;
}

Mat4 Mat4::rotationY(float theta)
{
    Mat4 rotationY; 

    float radians = theta * (pi / 180);
    float cos = cosf(radians);
    float sin = sinf(radians);

    rotationY.setElement(0, 0, cos);
    rotationY.setElement(0, 2, sin);
    rotationY.setElement(1, 1, 1.0f);
    rotationY.setElement(2, 0, -sin);
    rotationY.setElement(2, 2, cos);
    rotationY.setElement(3, 3, 1.0f);

    return rotationY;
}

Mat4 Mat4::rotationZ(float theta)
{
    Mat4 rotationZ; 

    float radians = theta * (pi / 180);
    float cos = cosf(radians);
    float sin = sinf(radians);

    rotationZ.setElement(0,0, cos);
    rotationZ.setElement(0, 1, -sin);
    rotationZ.setElement(1, 0, sin);
    rotationZ.setElement(1, 1, cos);
    rotationZ.setElement(2, 2, 1.0f);
    rotationZ.setElement(3, 3, 1.0f);

    return rotationZ;
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    Mat4 result; 

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                result.mat4[i][j] += this->mat4[i][k] * other.mat4[k][j];
            }
        }
    }

    return result;
}

Vec4 Mat4::operator*(const Vec4& other) const
{
    Vec4 res; 

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            res[i] += other[j] * this->mat4[i][j]; 
        }
    }

    return res; 
}   

Mat4 Mat4::operator+(const Mat4& other) const 
{
    Mat4 result; 

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            result.mat4[i][j] = this->mat4[i][j] + other.mat4[i][j];
        }
    }

    return result;
}

Mat4 Mat4::projectionTransform(float fov, float aspectRatio, float fNear, float fFar)
{
    Mat4 projection;

    float fFovRad = 1.0f / tanf(fov * 0.5f * pi / 180.0f);

    projection.setElement(0, 0, fFovRad / aspectRatio);
    projection.setElement(1, 1, fFovRad);
    projection.setElement(2, 2, fFar / (fFar - fNear));
    projection.setElement(2, 3, (-fFar * fNear) / (fFar - fNear));
    projection.setElement(3, 2, 1.0f);
    projection.setElement(3, 3, 0.0f);

    return projection;
}

Mat4 Mat4::viewportTransform(int width, int height)
{
    Mat4 viewport; 

    float widthRatio = 0.5 * width; 
    float heightRatio = 0.5 * height;

    viewport.setElement(0, 0, widthRatio);
    viewport.setElement(0, 3, widthRatio);
    viewport.setElement(1, 1, -heightRatio);
    viewport.setElement(1, 3, heightRatio);
    viewport.setElement(2, 2, 1);
    viewport.setElement(3, 3, 1);

    return viewport;
}

Mat4 Mat4::convertVectors(Vec4 a, Vec4 b, Vec4 c, Vec4 d)
{
    Mat4 res; 
    for(int i = 0; i < 4; i++)
    {
        res.setElement(i, 0, a[i]);
        res.setElement(i, 1, b[i]);
        res.setElement(i, 2, c[i]);
        res.setElement(i, 3, d[i]);
    }
    return res; 
}

Mat4 Mat4::convertVectors(Vec4 a, Vec4 b, Vec4 c)
{
    Mat4 res; 
    for(int i = 0; i < 4; i++)
    {
        res.setElement(i, 0, a[i]);
        res.setElement(i, 1, b[i]);
        res.setElement(i, 2, c[i]);
    }
    return res; 
}

void Mat4::toVectors(Vec4& a, Vec4& b, Vec4& c)
{
    for(int i = 0; i < 4; i++)
    {
        a[i] = getElement(i, 0);
        b[i] = getElement(i, 1);
        c[i] = getElement(i, 2);
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