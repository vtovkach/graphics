#include <stdexcept>
#include "v-math.hpp"

Triangle::Triangle(Vec4 A, Vec4 B, Vec4 C)
{
    vertices[0] = A;
    vertices[1] = B;
    vertices[2] = C;

    matrixForm = Transform::formMatrix(A, B, C);

    Vec4 x = {B.x - A.x, B.y - A.y, B.z - A.z, 0.0f};
    Vec4 y = {C.x - A.x, C.y - A.y, C.z - A.z, 0.0f};

    norm = Vec4::normalizeVec(Vec4::crossProduct(x, y));
}

Vec4 Triangle::operator[](int i) const
{
    if(i < 0 || i > 3) 
        throw std::runtime_error("Triangle::operator[]: index out of range");
        
    return vertices[i];
}

Mat4 Triangle::getMatrixForm() const
{
    return matrixForm;
}

void Triangle::transform(Mat4 transformation)
{
    matrixForm = transformation * this->matrixForm;
    matrixForm.toVectors(vertices[0], vertices[1], vertices[2]);
    
    Vec4 x = {vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].z - vertices[0].z, 0.0f};
    Vec4 y = {vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y, vertices[2].z - vertices[0].z, 0.0f};

    this->norm = Vec4::normalizeVec(Vec4::crossProduct(x, y));
}

void Triangle::updateState()
{
    matrixForm = Transform::formMatrix(vertices[0], vertices[1], vertices[2]);

    Vec4 x = {vertices[1].x - vertices[0].x, vertices[1].y - vertices[0].y, vertices[1].z - vertices[0].z, 0.0f};
    Vec4 y = {vertices[2].x - vertices[0].x, vertices[2].y - vertices[0].y, vertices[2].z - vertices[0].z, 0.0f};

    this->norm = Vec4::normalizeVec(Vec4::crossProduct(x, y));
}