#pragma once

#include <SDL3/SDL.h>

#include <cstdint>
#include <vector>

#include <camera.hpp>

class Window
{
public:
    explicit Window(const char* title, int width, int height);
    ~Window();

    void handleEvents();
    void drawScreen(const uint32_t *framebuffer);

    bool isActive() const;

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    int width;
    int height;

    bool active = true;
};