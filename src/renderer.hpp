#pragma once 

#include <vector>
#include <cstdint>

class Renderer
{
public:
    explicit Renderer(int width, int height);
    ~Renderer();

    void drawLine();
    void fillTriangle();  
    std::vector<uint32_t>& getFrameBuffer();

private:
    int dimX; 
    int dimY;
    std::vector<uint32_t> frameBuffer;
};