#pragma once

#include <cstdint>
#include <limits>
#include <iostream>

struct Stats
{
    double totalRenderTimeMs = 0.0;
    double totalTriangleRenderTimeMs = 0.0;
    uint64_t totalRenderFrames = 0;
    uint64_t totalPixels = 0;
    uint64_t totalTriangles = 0;

    double frameRenderTimeMs = 0.0;
    double avgFrameRenderTimeMs = 0.0;
    double minFrameRenderTimeMs = std::numeric_limits<double>::infinity();
    double maxFrameRenderTimeMs = 0.0;

    double pixelsPerSec = 0.0;
    double trianglesPerSec = 0.0;
    double avgTimePerTriangleMs = 0.0;

    void printStatistics() const;
    void updateStatistics(); 
};

