#pragma once 

#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>

#include "object3D.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "math.hpp"

#pragma pack(push, 1)

struct Pixel
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0; 
    uint8_t a = 255; 
};

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b; 
};

#pragma pack(pop)

class Renderer
{
public:
    explicit Renderer(int width, int height);
    ~Renderer();

    void renderObject(Object3D& obj, Camera& camera, Lighting& light);

    void drawPixel(int x, int y, Color color, float brightness);
    void drawLine(Vec4 A, Vec4 B, Color color);
    void fillTriangle(Vec4 A, Vec4 B, Vec4 C, Color color, float brightness);  
    std::vector<Pixel>& getFrameBuffer();

private:
    int width; 
    int height;
    float fov;
    float fNear;
    float fFar;

    std::vector<Pixel> frameBuffer;

    Mat4 projectionTransform;
    Mat4 viewportTransform;
};