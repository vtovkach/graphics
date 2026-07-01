#include "playground.hpp"

#include <thread>
#include <chrono>

constexpr const char* DEFAULT_TITLE = "Renderer";
constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;
constexpr int SLEEP_TIME = 16; // 60FPS

PlayGround::PlayGround() : window(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT), renderer(DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

PlayGround::PlayGround(const char *title, int width, int height) : window(title, width, height), renderer(width ,height)
{
}

void PlayGround::run()
{
    while(window.isActive())
    {   
        Camera camera = activeScene.getCamera();
        Lighting light = activeScene.getLighting();        
        std::vector<Object3D>& objects = activeScene.getObjects();

        renderer.clearFrameBuffer();
        renderer.clearDepthBuffer();
        for(auto& obj : objects)
        {
            obj.rotateObject(0.0f, 1.0f, 0.5f);
            renderer.renderObject(obj, camera, light);
        }

        std::vector<Pixel> framebuf = renderer.getFrameBuffer(); 
        const uint32_t *pixels = reinterpret_cast<const uint32_t *>(framebuf.data());
        window.drawScreen(pixels);

        window.handleEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }
}

void PlayGround::addObject(std::string objectPath, Vec4 initPosition)
{
    Object3D obj(objectPath);
    obj.setObjPos(initPosition.x, initPosition.y, initPosition.z);

    activeScene.addObject(obj);
}