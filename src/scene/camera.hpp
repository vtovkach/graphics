#pragma once 

#include "math.hpp"

class Camera
{
public:
    Camera();

    bool doesTriangleFaceCamera(Triangle tri) const;

    void moveX();
    void moveY();
    void moveZ();
    void setPosition(float x, float y, float z);

    void pitch();
    void yaw();
    void roll();

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