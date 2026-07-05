#include "window.hpp"
#include <stdexcept>

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

void Window::handleEvents(Camera& camera) 
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) 
    {
        if (event.type == SDL_EVENT_QUIT) {
            active = false;
        }

        if(event.type == SDL_EVENT_KEY_DOWN)
        {
            if(event.key.key == SDLK_W){
            camera.move(0, 0, 1);
            }
            else if(event.key.key == SDLK_S){
                camera.move(0, 0, -1);
            }
            else if(event.key.key == SDLK_A){
                camera.move(-1, 0, 0);
            }
            else if(event.key.key == SDLK_D){
                camera.move(1, 0, 0);
            }
            else if(event.key.key == SDLK_Q){
                camera.rotateY(-1);
            }
            else if(event.key.key == SDLK_E){
                camera.rotateY(1);
            }
            else if(event.key.key == SDLK_R){
                camera.rotateX(-1);
            }
            else if(event.key.key == SDLK_F){
                camera.rotateX(1);
            }
        }
    }
}

bool Window::isActive() const
{
    return active;
}

void Window::drawScreen(const uint32_t *framebuffer)
{
    // Update the texture 
    SDL_UpdateTexture(texture, nullptr, framebuffer, width * sizeof(uint32_t));

    // Apply texture to the screen
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}