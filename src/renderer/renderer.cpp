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
    depthBuffer.resize(width * height);
    this->clearDepthBuffer();
}

void Renderer::clearFrameBuffer()
{
    std::fill(frameBuffer.begin(), frameBuffer.end(), Pixel());
}

void Renderer::clearDepthBuffer()
{
    std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::infinity());
}

void Renderer::drawPixel(int x, int y, Color color, float brightness)
{
    if(x >= width || y >= height || x < 0 || y < 0) 
        return; 

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

    minX = std::max(minX, 0);
    maxX = std::min(maxX, width - 1);
    minY = std::max(minY, 0);
    maxY = std::min(maxY, height - 1);

    float ABCarea = triArea(A, B, C); 
    if(ABCarea < 1e-6f) return; // Degenerate triangle

    for(int x = minX; x < maxX; x++)
    {
        for(int y = minY; y < maxY; y++)
        {
            Vec4 P = {x + 0.5f, y + 0.5f, 0, 1};

            float alpha = triArea(B, C, P) / ABCarea; 
            float beta = triArea(C, A, P) / ABCarea; 
            float gamma = triArea(A, B, P) / ABCarea;

            if(alpha < 0.0f || beta < 0.0f || gamma < 0.0f) 
                continue;  // Point is not inside a triangle

            // Depth Test
            float z = alpha * A.z + beta * B.z + gamma * C.z;
            if(depthBuffer[y * width + x] < z) 
                continue;
            depthBuffer[y * width + x] = z;

            drawPixel((int)P.x, (int)P.y, color, brightness); 
        }
    }
}

const std::vector<Pixel>& Renderer::getFrameBuffer() const 
{
    return frameBuffer;
}

void Renderer::renderObject(const Object3D& obj, const Camera& camera, const Lighting& light)
{
    Mat4 modelTransform = obj.getModelTransform();
    Mesh objMesh = obj.getObjectMesh();

    projectionTransform = Transform::projectionTransform(
        fov, 
        static_cast<float>(width) / static_cast<float>(height), 
        fNear, 
        fFar
    );

    viewportTransform = Transform::viewportTransform(width, height);

    for(auto& triangle : objMesh.triangles)
    {
        Vec4 vertexA = triangle.vertices[0];
        Vec4 vertexB = triangle.vertices[1];
        Vec4 vertexC = triangle.vertices[2];

        // Model Transformation 
        vertexA = modelTransform * vertexA;
        vertexB = modelTransform * vertexB;
        vertexC = modelTransform * vertexC;

        // Recompute normal 
        triangle.norm = Vec4::normalizeVec(Vec4::crossProduct(
            {vertexB.x - vertexA.x, vertexB.y - vertexA.y, vertexB.z - vertexA.z, 0.0f},
            {vertexC.x - vertexA.x, vertexC.y - vertexA.y, vertexC.z - vertexA.z, 0.0f}
        ));

        // Back-face culling
        Vec4 cameraDir = {camera.camera.x - vertexA.x, camera.camera.y - vertexA.y, camera.camera.z - vertexA.z, 0.0f};
        cameraDir = Vec4::normalizeVec(cameraDir);
        float dot = Vec4::dotProduct(triangle.norm, cameraDir);
        if(dot <= 0) continue;

        // Take lighting into account
        Vec4 lightDir = {
            light.lightDirection.x - vertexA.x, 
            light.lightDirection.y - vertexA.y, 
            light.lightDirection.z - vertexA.z, 0.0f
        }; 
        lightDir = Vec4::normalizeVec(lightDir);

        float lightDot = Vec4::dotProduct(lightDir, triangle.norm);

        // Projection Transformation
        vertexA = projectionTransform * vertexA;
        vertexB = projectionTransform * vertexB;
        vertexC = projectionTransform * vertexC;

        if(vertexA.w != 0.0f)
        {
            vertexA.x /= vertexA.w;
            vertexA.y /= vertexA.w;
            vertexA.z /= vertexA.w;
            vertexA.w = 1;
        }
        if(vertexB.w != 0.0f)
        {
            vertexB.x /= vertexB.w;
            vertexB.y /= vertexB.w;
            vertexB.z /= vertexB.w;
            vertexB.w = 1;
        }
        if(vertexC.w != 0.0f)
        {
            vertexC.x /= vertexC.w;
            vertexC.y /= vertexC.w;
            vertexC.z /= vertexC.w;
            vertexC.w = 1;
        }

        // Viewport transformation 
        vertexA = viewportTransform * vertexA;
        vertexB = viewportTransform * vertexB;
        vertexC = viewportTransform * vertexC;

        fillTriangle(vertexA, vertexB, vertexC, {255, 255, 255}, lightDot);
    }
}