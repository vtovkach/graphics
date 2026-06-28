#include "renderer.hpp"

constexpr float DEFAULT_FOV = 90.0f; // in degrees
constexpr float DEFAULT_NEAR = 0.1f;
constexpr float DEFAULT_FAR = 1000.0f; 

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
        .r = color.r * brightness, 
        .g = color.g * brightness, 
        .b = color.b * brightness
    }; 

    frameBuffer[y * width + x] = pixel;
}

void Renderer::drawLine()
{

}

void Renderer::fillTriangle()
{

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
        // Apply modelTransform
        // Apply projectionTransform
        // Apply viewPortTransform

        // Display triangle 

        // Take lighting into account (dot product)
    }
}

void Renderer::renderTriangle()
{

}