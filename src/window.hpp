#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <algorithm>

#include "math3d.hpp"

class Window
{
private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    int width; 
    int height;
    bool running; 
public:
    Window(const char *title, int width, int height);
    ~Window();

    void handleEvents();
    void clear();
    void drawLine(float x1, float y1, float x2, float y2);
    void drawPixel(int x, int y, float brightness);
    void drawTriangle(vec3d vertex1, vec3d vertex2, vec3d vertex3);
    void fillTriangle(vec3d v1, vec3d v2, vec3d v3, float brightness);
    void present();
    bool isRunning();
};