#include "renderer.hpp"

constexpr float DEFAULT_FOV = 90.0f; // in degrees
constexpr float DEFAULT_NEAR = 0.1f;
constexpr float DEFAULT_FAR = 1000.0f;

// Helper functions 
namespace 
{
    float triArea(Vec4 A, Vec4 B, Vec4 C)
    {
        return  ((B.x - A.x) * (C.y - A.y)) - 
                ((B.y - A.y) * (C.x - A.x));
    }  
}

Renderer::Renderer(int width, int height) 
    : width(width), 
      height(height), 
      fov(DEFAULT_FOV), 
      fNear(DEFAULT_NEAR), 
      fFar(DEFAULT_FAR)
{
    frameBuffer.resize(width * height, Pixel());
}

void Renderer::drawPixel(int x, int y, Color color, float brightness)
{
    Pixel pixel = {
        .r = static_cast<uint8_t>(color.r * brightness),
        .g = static_cast<uint8_t>(color.g * brightness),
        .b = static_cast<uint8_t>(color.b * brightness),
    }; 

    frameBuffer[y * width + x] = pixel;
}

void Renderer::drawLine(Vec4 A, Vec4 B, Color color)
{

}

void Renderer::fillTriangle(Vec4 A, Vec4 B, Vec4 C, Color color, float brightness)
{
    int minX = (int)std::floor(std::min({A.x, B.x, C.x})); 
    int maxX = (int)std::ceil(std::max({A.x, B.x, C.x}));
    int minY = (int)std::floor(std::min({A.y, B.y, C.y}));
    int maxY = (int)std::ceil(std::max({A.y, B.y, C.y}));

    float ABCarea = triArea(A, B, C); 
    if(ABCarea == 1e-6f) return; // Degenerate triangle

    for(int x = minX; x < maxX; x++)
    {
        for(int y = minY; y < maxY; y++)
        {
            Vec4 P = {x + 0.5f, y + 0.5f, 0, 1};

            float alpha = triArea(B, C, P) / ABCarea; 
            float beta = triArea(C, A, P) / ABCarea; 
            float gamma = triArea(A, B, P) / ABCarea;

            if(alpha < 0.0f || beta < 0.0f || gamma < 0.0f) 
                continue;  // Point is not inside triangle

            drawPixel((int)std::round(P.x), (int)std::round({P.y}), color, brightness); 
        }
    }
}

std::vector<Pixel>& Renderer::getFrameBuffer()
{
    return frameBuffer;
}

void Renderer::renderObject(Object3D& obj, Camera& camera, Lighting& light)
{
    Mat4 modelTransform = obj.getModelTransform();
    Mesh objMesh = obj.getObjectMesh();

    projectionTransform = Mat4::projectionTransform(
        fov, 
        static_cast<float>(width) / static_cast<float>(height), 
        fNear, 
        fFar
    );

    for(auto& triangle : objMesh.triangles)
    {
        // Implement a back-face culling here 
        // TODO 
        // ... 

        Mat4 triangleMatrix = Mat4::convertVectors(triangle.vertices[0], triangle.vertices[1], triangle.vertices[2]); 

        triangleMatrix = modelTransform * triangleMatrix;
        triangleMatrix = projectionTransform * triangleMatrix;
        triangleMatrix = viewportTransform * triangleMatrix;

        // Perspective Divide 
        // TODO

        // Take lighting into account (dot product)
        // TODO 
        // ... 

        Vec4 a;
        Vec4 b;
        Vec4 c;
        triangleMatrix.toVectors(a, b, c);

        fillTriangle(a, b, c, {255, 255, 255}, 1.0f);
    }
}