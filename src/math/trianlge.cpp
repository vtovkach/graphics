#include "math.hpp"

Triangle::Triangle(Vec4 A, Vec4 B, Vec4 C)
{
    vertices[0] = A;
    vertices[1] = B;
    vertices[2] = C;

    Vec4 x = {B.x - A.x, B.y - A.y, B.z - A.z, 0.0f};
    Vec4 y = {C.x - A.x, C.y - A.y, C.z - A.z, 0.0f};

    norm = Vec4::crossProduct(x, y);
    norm = Vec4::normalizeVec(norm);
}