#include "camera.hpp"

bool Camera::doesTriangleFaceCamera(Triangle tri) const
{
    Vec4 vectorFromTriangleToCamera = {
        cameraPosition.x - tri.vertices[0].x, 
        cameraPosition.y - tri.vertices[0].y, 
        cameraPosition.z - tri.vertices[0].z, 
        0.0f
    };

    vectorFromTriangleToCamera = Vec4::normalizeVec(vectorFromTriangleToCamera);   

    float dot = Vec4::dotProduct(tri.norm, vectorFromTriangleToCamera);

    return (dot > 0) ? true : false; 
}