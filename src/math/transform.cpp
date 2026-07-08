#include "v-math.hpp"

Mat4 Transform::formMatrix(const Vec4& a, const Vec4& b, const Vec4& c)
{
    Mat4 res; 

    for(int i = 0; i < 4; i++)
    {
        res.setElement(i, 0, a[i]);
        res.setElement(i, 1, b[i]);
        res.setElement(i, 2, c[i]);
        /* 4th column is skipped */
    }

    return res; 
}

Mat4 Transform::projectionTransform(float fov, float aspectRatio, float fNear, float fFar)
{
    Mat4 projection;

    float fFovRad = 1.0f / tanf(fov * 0.5f * pi / 180.0f);

    projection.setElement(0, 0, fFovRad / aspectRatio);
    projection.setElement(1, 1, fFovRad);
    projection.setElement(2, 2, fFar / (fFar - fNear));
    projection.setElement(2, 3, (-fFar * fNear) / (fFar - fNear));
    projection.setElement(3, 2, 1.0f);
    projection.setElement(3, 3, 0.0f);

    return projection;
}

Mat4 Transform::viewportTransform(int width, int height)
{
    Mat4 viewport; 

    float widthRatio = 0.5 * width; 
    float heightRatio = 0.5 * height;

    viewport.setElement(0, 0, widthRatio);
    viewport.setElement(0, 3, widthRatio);
    viewport.setElement(1, 1, -heightRatio);
    viewport.setElement(1, 3, heightRatio);
    viewport.setElement(2, 2, 1);
    viewport.setElement(3, 3, 1);

    return viewport;
}

Mat4 Transform::translateTransform(float x, float y, float z)
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

Mat4 Transform::scaleTransform(float sx, float sy, float sz)
{
    Mat4 scaleTransform;

    scaleTransform.setElement(0, 0, sx);
    scaleTransform.setElement(1, 1, sy);
    scaleTransform.setElement(2, 2, sz);
    scaleTransform.setElement(3, 3, 1);

    return scaleTransform;
}

Mat4 Transform::rotationXTransform(float theta)
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

Mat4 Transform::rotationYTransform(float theta)
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

Mat4 Transform::rotationZTransform(float theta)
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

Mat4 Transform::cameraTransform(Vec4 cameraPosition, Vec4 right, Vec4 up, Vec4 forward)
{
    Mat4 translation;
    translation.setElement(0, 0, 1);
    translation.setElement(0, 3, -cameraPosition.x);
    translation.setElement(1, 1, 1);
    translation.setElement(1, 3, -cameraPosition.y);
    translation.setElement(2, 2, 1);
    translation.setElement(2, 3, -cameraPosition.z);
    translation.setElement(3, 3, 1);

    Mat4 changeBasis;
    changeBasis.setElement(0, 0, right.x);
    changeBasis.setElement(0, 1, right.y);
    changeBasis.setElement(0, 2, right.z);
    changeBasis.setElement(1, 0, up.x);
    changeBasis.setElement(1, 1, up.y);
    changeBasis.setElement(1, 2, up.z);
    changeBasis.setElement(2, 0, forward.x);
    changeBasis.setElement(2, 1, forward.y);
    changeBasis.setElement(2, 2, forward.z);
    changeBasis.setElement(3, 3, 1);
    
    return changeBasis * translation; 
}

Mat4 Transform::rotationAroundAxis(Vec4 axis, float theta)
{
    axis = Vec4::normalizeVec(axis);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    float c = cos(theta);
    float s = sin(theta);
    float t = 1.0f - c;

    Mat4 r;

    r.setElement(0, 0, t*x*x + c);
    r.setElement(0, 1, t*x*y - s*z);
    r.setElement(0, 2, t*x*z + s*y);

    r.setElement(1, 0, t*x*y + s*z);
    r.setElement(1, 1, t*y*y + c);
    r.setElement(1, 2, t*y*z - s*x);

    r.setElement(2, 0, t*x*z - s*y);
    r.setElement(2, 1, t*y*z + s*x);
    r.setElement(2, 2, t*z*z + c);

    r.setElement(3, 3, 1.0f);

    return r;
}