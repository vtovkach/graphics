#include "lighting.hpp"

float Lighting::computerBrightness(Triangle tri) const
{
    Vec4 lightDir = {
        lightSourcePos.x - tri.vertices[0].x,
        lightSourcePos.y - tri.vertices[0].y,
        lightSourcePos.z - tri.vertices[0].z,
        0.0f
    };

    lightDir = Vec4::normalizeVec(lightDir);

    return Vec4::dotProduct(lightDir, tri.norm);
}

Vec4 Lighting::getPosition() const
{
    return lightSourcePos;
}