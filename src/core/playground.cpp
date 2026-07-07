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
    Scene activeScene;
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
    while (impl->window.isActive())
    {   
        Camera& camera = impl->activeScene.getCamera();
        Lighting light = impl->activeScene.getLighting();        
        std::vector<Object3D>& objects = impl->activeScene.getObjects();

        impl->renderer.clearFrameBuffer();
        impl->renderer.clearDepthBuffer();

        for (auto& obj : objects)
        {
            obj.rotateObject(0.0f, 1.0f, 0.5f);
            impl->renderer.renderObject(obj, camera, light);
        }

        std::vector<Pixel> framebuf = impl->renderer.getFrameBuffer(); 
        const uint32_t* pixels = reinterpret_cast<const uint32_t*>(framebuf.data());

        impl->window.drawScreen(pixels);
        impl->window.handleEvents(camera);

        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }

    Stats rendererStats = impl->renderer.getStatistics();
    rendererStats.printStatistics();
}

void PlayGround::addObject(std::string objectPath, Vec4 initPosition)
{
    Object3D obj(objectPath);
    obj.setObjPos(initPosition.x, initPosition.y, initPosition.z);

    impl->activeScene.addObject(obj);
}