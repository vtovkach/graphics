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
    Scene* activeScene;
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
            impl->renderer.renderObject(*obj, impl->activeScene);
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

void PlayGround::addScene(std::unique_ptr<Scene> scene)
{
    if (!scene)
    {
        throw std::invalid_argument("Scene cannot be null");
    }

    std::string sceneId = scene->getId();

    auto [it, inserted] =
        impl->scenes.emplace(sceneId, std::move(scene));

    if (!inserted)
    {
        throw std::runtime_error(
            "Scene already exists: " + sceneId
        );
    }
}

void PlayGround::deleteScene(const std::string& sceneId)
{
    auto it = impl->scenes.find(sceneId);

    if (it == impl->scenes.end())
    {
        throw std::runtime_error(
            "Scene does not exist: " + sceneId
        );
    }

    if (it->second.get() == impl->activeScene)
    {
        throw std::runtime_error(
            "Cannot remove active scene: " + sceneId
        );
    }

    impl->scenes.erase(it);
}

void PlayGround::setActiveScene(const std::string& sceneId)
{
    auto it = impl->scenes.find(sceneId);
    if(it == impl->scenes.end())
    {
        throw std::runtime_error("Scene does not exist: " + sceneId);
    }

    impl->activeScene = it->second.get();
}

Scene* PlayGround::getScene(const std::string& sceneId) const
{
    auto it = impl->scenes.find(sceneId);
    if(it == impl->scenes.end())
    {
        throw std::runtime_error("Scene does not exist: " + sceneId);
    }

    return it->second.get();
}

Scene* PlayGround::getActiveScene() const
{
    return impl->activeScene;
}