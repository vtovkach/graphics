#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "scene.hpp"

#include <string>

class PlayGround
{
public:
    PlayGround();
    explicit PlayGround(const char *title, int width, int height);

    void addObject(std::string objectPath, Vec4 initPosition);

    void run();

private:
    Window window; 
    Renderer renderer;     
    Scene activeScene;  
};