#pragma once 

#include "playground.hpp"
#include <memory>

class Example : public PlayGround
{
public:
    Example(const char *title, int width, int height) : PlayGround(title, width, height)
    {
    }

private:
    void _ready() override
    {
        std::unique_ptr<Scene> scene = std::make_unique<Scene>("main");
        addScene(std::move(scene));
        setActiveScene(std::string("main"));

        std::unique_ptr<Object3D> obj = std::make_unique<Object3D>("res/VideoShip.obj", "ship");

        Scene *activeScene = getActiveScene();
        activeScene->addObject(std::move(obj));
    }

    void _process(Scene *activeScene) override
    {
        Object3D *obj = activeScene->getObject("ship");
        obj->rotateObject(0.55, 0, 0.30);
    }

    void _keyPressed(Keycode key) override
    {
        std::cout << "Key Pressed" << std::endl;
    }

    void _keyReleased(Keycode key) override
    {
        std::cout << "Key released" << std::endl;
    }
};