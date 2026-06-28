#include <cmath>
#include "math.hpp"

Mat4::Mat4() : mat4{}{};

void Mat4::setElement(int row, int column, float data)
{
    mat4[row][column] = data;
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