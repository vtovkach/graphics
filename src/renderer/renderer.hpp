#pragma once 

#include <vector>
#include <algorithm>
#include <cmath>

#include "object3D.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "v-math.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "render_stats.hpp"

class Renderer
{
public:
    explicit Renderer(int width, int height);

    void renderObject(const Object3D& obj, const Camera& camera, const Lighting& light);

    void clearFrameBuffer();
    void clearDepthBuffer();

    const std::vector<Pixel>& getFrameBuffer() const;

    const Stats& getStatistics() const;

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

    Stats stats; // Measure the performance of the renderer

    void drawPixel(int x, int y, Color color, float brightness);
    void drawLine(Vec4 A, Vec4 B, Color color);
    void fillTriangle(Vec4 A, Vec4 B, Vec4 C, Color color, float brightness);  
};