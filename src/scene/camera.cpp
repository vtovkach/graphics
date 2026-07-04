#include "camera.hpp"

Camera::Camera()
{
    cameraPosition = {0, 0, 0, 1};

    cameraSpeed = 0.15f;
    rotationSpeed = 0.15f;

    forward = {0, 0, 1, 1};
    up      = {0, 1, 0, 1};
    right   = {1, 0, 0, 1};

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

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

void Camera::moveX()
{
    cameraPosition.x += cameraSpeed;
    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::moveY()
{
    cameraPosition.y += cameraSpeed;
    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::moveZ()
{
    cameraPosition.z += cameraSpeed;
    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::pitch()
{
    Mat4 rotation = Transform::rotationXTransform(rotationSpeed);

    right = Vec4::normalizeVec(rotation * right);
    up = Vec4::normalizeVec(rotation * up);
    forward = Vec4::normalizeVec(rotation * forward);

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::yaw()
{
    Mat4 rotation = Transform::rotationYTransform(rotationSpeed);

    right = Vec4::normalizeVec(rotation * right);
    up = Vec4::normalizeVec(rotation * up);
    forward = Vec4::normalizeVec(rotation * forward);

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::roll()
{
    Mat4 rotation = Transform::rotationZTransform(rotationSpeed);

    right = Vec4::normalizeVec(rotation * right);
    up = Vec4::normalizeVec(rotation * up);
    forward = Vec4::normalizeVec(rotation * forward);

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

Mat4 Camera::getCameraTransform() const
{
    return cameraTransformation;
}