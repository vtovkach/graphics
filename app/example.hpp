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
    }
    void _process() override
    {
    }

    void _keyPressed() override
    {
    }

    void _keyReleased() override
    {
    }
};