#include "camera.hpp"

constexpr float DEFAULT_CAM_SPEED = 0.15f;
constexpr float DEFAULT_CAM_ROT_SPEED = 0.15f;

Camera::Camera()
{
    cameraPosition = {0, 0, 10, 1};

    cameraSpeed = DEFAULT_CAM_SPEED;
    rotationSpeed = DEFAULT_CAM_ROT_SPEED;

    forward = {0, 0, -1, 0}; /* direction into the screen is negative z */
    up      = {0, 1, 0, 0};
    right   = {1, 0, 0, 0};

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::setRotation(float thetaX, float thetaY, float thetaZ)
{
    // Roll -> Pitch -> Yaw
    Mat4 rotationTransform = Transform::rotationYTransform(thetaY)   *
                             Transform::rotationXTransform(thetaX)   *
                             Transform::rotationZTransform(thetaZ);

    right = {1, 0 ,0, 0};
    up = {0, 1, 0, 0};
    forward = {0, 0, 1, 0};
    
    right = rotationTransform * right;
    up = rotationTransform * up;
    forward = rotationTransform * forward;

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::rotateX(float theta)
{
    Mat4 rotationTransform = Transform::rotationAroundAxis(right, theta * rotationSpeed);

    right = rotationTransform * right;
    up = rotationTransform * up;
    forward = rotationTransform * forward;

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::rotateY(float theta)
{
    Mat4 rotationTransform = Transform::rotationAroundAxis(up, theta * rotationSpeed);

    right = rotationTransform * right;
    up = rotationTransform * up;
    forward = rotationTransform * forward;

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::rotateZ(float theta)
{
    Mat4 rotationTransform = Transform::rotationAroundAxis(forward, theta * rotationSpeed);

    right = rotationTransform * right;
    up = rotationTransform * up;
    forward = rotationTransform * forward;

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::setPosition(float x, float y, float z)
{
    cameraPosition.x = x;
    cameraPosition.y = y;
    cameraPosition.z = z;
    cameraPosition.w = 1;

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

void Camera::move(float dx, float dy, float dz)
{
    Vec4 movement; 
    movement.x = right.x * dx + up.x * dy + forward.x * dz;
    movement.y = right.y * dx + up.y * dy + forward.y * dz;
    movement.z = right.z * dx + up.z * dy + forward.z * dz;
    movement.w = 0.0f;

    cameraPosition.x+= movement.x * cameraSpeed;
    cameraPosition.y+= movement.y * cameraSpeed;
    cameraPosition.z+= movement.z * cameraSpeed;

    cameraTransformation = Transform::cameraTransform(cameraPosition, right, up, forward);
}

Mat4 Camera::getCameraTransform() const
{
    return cameraTransformation;
}

Vec4 Camera::getPosition() const
{
    return cameraPosition;
}