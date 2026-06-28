#pragma once

#include "window.hpp"
#include "renderer.hpp"
#include "sceneManager.hpp"

class PlayGround
{
public:
    PlayGround();
    explicit PlayGround(const char *title, int width, int height);
    ~PlayGround();

    void run();

private:
    Window window; 
    Renderer renderer;     
    SceneManager sceneManager; 
};