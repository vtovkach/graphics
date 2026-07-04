#include "render_stats.hpp"

void Stats::printStatistics() const
{
    std::cout << "\n========== Renderer Statistics ==========\n";

    std::cout << "Render time:\n";
    std::cout << "  Current frame:       " << frameRenderTimeMs << " ms\n";
    std::cout << "  Average frame:       " << avgFrameRenderTimeMs << " ms\n";
    std::cout << "  Min frame:           " << minFrameRenderTimeMs << " ms\n";
    std::cout << "  Max frame:           " << maxFrameRenderTimeMs << " ms\n";
    std::cout << "  Total render time:   " << totalRenderTimeMs << " ms\n";

    std::cout << "\nCounters:\n";
    std::cout << "  Frames rendered:     " << totalRenderFrames << '\n';
    std::cout << "  Pixels drawn:        " << totalPixels << '\n';
    std::cout << "  Triangles rendered:  " << totalTriangles << '\n';

    std::cout << "\nThroughput:\n";
    std::cout << "  Pixels/sec:          " << pixelsPerSec << '\n';
    std::cout << "  Triangles/sec:       " << trianglesPerSec << '\n';

    std::cout << "  Avg time/triangle:   " << avgTimePerTriangleMs << " ms\n";

    std::cout << "=========================================\n";
}

void Stats::updateStatistics()
{
    if (totalRenderFrames > 0)
    {
        avgFrameRenderTimeMs = totalRenderTimeMs / totalRenderFrames;
    }

    minFrameRenderTimeMs = std::min(minFrameRenderTimeMs, frameRenderTimeMs);
    maxFrameRenderTimeMs = std::max(maxFrameRenderTimeMs, frameRenderTimeMs);

    if (totalRenderTimeMs > 0.0)
    {
        pixelsPerSec =
            totalPixels / (totalRenderTimeMs / 1000.0);

        trianglesPerSec =
            totalTriangles / (totalRenderTimeMs / 1000.0);
    }

    if (totalTriangles > 0)
    {
        avgTimePerTriangleMs =
            totalTriangleRenderTimeMs / totalTriangles;
    }
}