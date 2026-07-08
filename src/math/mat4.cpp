#include "v-math.hpp"

Mat4::Mat4() : mat4 {}{};

void Mat4::setElement(int row, int column, float data)
{
    mat4[row][column] = data;
}

float Mat4::getElement(int row, int column) const
{
    return mat4[row][column];
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    Mat4 result; 

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            for(int k = 0; k < N; k++)
            {
                result.mat4[i][j] += this->mat4[i][k] * other.mat4[k][j];
            }
        }
    }

    return result;
}

Vec4 Mat4::operator*(const Vec4& other) const
{
    Vec4 result;

    for (int i = 0; i < N; i++)
    {
        result[i] =
            mat4[i][0] * other[0] +
            mat4[i][1] * other[1] +
            mat4[i][2] * other[2] +
            mat4[i][3] * other[3];
    }

    return result;
}

Mat4 Mat4::operator+(const Mat4& other) const 
{
    Mat4 result; 

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            result.mat4[i][j] = this->mat4[i][j] + other.mat4[i][j];
        }
    }

    return result;
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