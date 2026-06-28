#include "window.hpp"
#include <stdexcept>

constexpr const char* DEFAULT_TITLE = "Renderer";
constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;

Window::Window() : Window(DEFAULT_TITLE, DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

Window::Window(const char *title, int width, int height) : width(width), height(height)
{
    if(!SDL_Init(SDL_INIT_VIDEO)){
        throw std::runtime_error(
            std::string("SDL_Init failed.") + SDL_GetError()
        );
    }

    window = SDL_CreateWindow(title, width, height, 0);
    if(!window){
        throw std::runtime_error(
            std::string("SDL_CreateWindow failed.") + SDL_GetError()
        );
    }
    
    renderer = SDL_CreateRenderer(window, nullptr);
    if(!renderer)
    {
        throw std::runtime_error(
            std::string("SDL_CreateRenderer failed.") + SDL_GetError()
        );
    }

    texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        width, 
        height
    );
    if(!texture)
    {
        throw std::runtime_error(
            std::string("SDL_CreateTexture failed.") + SDL_GetError()
        );
    }
}

Window::~Window()
{
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    if(texture) SDL_DestroyTexture(texture);
    SDL_Quit();
}

void Window::handleEvents() 
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            active = false;
        }
    }
}

bool Window::isActive() const
{
    return active;
}

void Window::drawScreen(const std::vector<uint32_t>& framebuffer)
{
    // Update the texture 
    SDL_UpdateTexture(texture, nullptr, framebuffer.data(), width * sizeof(uint32_t));

    // Apply texture to the screen
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}