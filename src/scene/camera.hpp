#pragma once 

#include "math.hpp"

class Camera
{
public:
    Camera();

    bool doesTriangleFaceCamera(Triangle tri) const;

    void setRotation(float thetaX, float thetaY, float thetaZ);
    void rotateX(float theta);
    void rotateY(float theta);
    void rotateZ(float theta);

    void setPosition(float x, float y, float z);
    void move(float dx, float dy, float dz);

    Mat4 getCameraTransform() const;

private:
    Vec4 cameraPosition;

    float cameraSpeed;
    float rotationSpeed;

    // Ortonormal basis of camera's orientation
    Vec4 right;
    Vec4 up; 
    Vec4 forward;

    Mat4 cameraTransformation; 
};