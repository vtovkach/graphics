#include "playground.hpp"

#include "window.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include "object3D.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "render_stats.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <unordered_map>

constexpr const char* DEFAULT_TITLE = "Renderer";
constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;
constexpr int SLEEP_TIME = 16; // ~60 FPS

class PlayGround::Impl 
{
public:
    Impl(const char* title, int width, int height)
        : window(title, width, height),
          renderer(width, height)
    {
    }

    Window window;
    Renderer renderer;

    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes; 
    std::unique_ptr<Scene> activeScene;
};

PlayGround::PlayGround()
    : impl(std::make_unique<Impl>(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT))
{
}

PlayGround::PlayGround(const char* title, int width, int height)
    : impl(std::make_unique<Impl>(title, width, height))
{
}

PlayGround::~PlayGround() = default;

void PlayGround::run()
{
    _ready(); // User implemented function

    while (impl->window.isActive())
    {   
        _process(); // User implemented function
        
        impl->renderer.clearFrameBuffer();
        impl->renderer.clearDepthBuffer();

        for (auto it = impl->activeScene->objectsStart(); it != impl->activeScene->objectsEnd(); it++)
        {
            Object3D *obj = it->second.get();
            impl->renderer.renderObject(*obj, impl->activeScene.get());
        }

        std::vector<Pixel> framebuf = impl->renderer.getFrameBuffer(); 
        const uint32_t* pixels = reinterpret_cast<const uint32_t*>(framebuf.data());

        impl->window.drawScreen(pixels);
        impl->window.handleEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }

    Stats rendererStats = impl->renderer.getStatistics();
    rendererStats.printStatistics();
}