#pragma once 

#include <vector>
#include <algorithm>
#include <cmath>

#include "object3D.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "math.hpp"
#include "color.hpp"
#include "pixel.hpp"

class Renderer
{
public:
    explicit Renderer(int width, int height);

    void renderObject(const Object3D& obj, const Camera& camera, const Lighting& light);

    void clearFrameBuffer();
    void clearDepthBuffer();

    const std::vector<Pixel>& getFrameBuffer() const;

private:
    int width; 
    int height;
    float fov;
    float fNear;
    float fFar;

    std::vector<Pixel> frameBuffer;
    std::vector<float> depthBuffer;

    Mat4 projectionTransform;
    Mat4 viewportTransform;

    void drawPixel(int x, int y, Color color, float brightness);
    void drawLine(Vec4 A, Vec4 B, Color color);
    void fillTriangle(Vec4 A, Vec4 B, Vec4 C, Color color, float brightness);  
};